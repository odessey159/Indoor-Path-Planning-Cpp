import json
import requests
from flask import Flask, request, jsonify
from openai import OpenAI

app = Flask(__name__)

OPENROUTER_API_KEY = "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"
MODEL_NAME = "deepseek/deepseek-v3.2"
CPP_BASE = "http://localhost:8081"

client = OpenAI(
    api_key=OPENROUTER_API_KEY,
    base_url="https://openrouter.ai/api/v1"
)

def plan_route(start: str, end: str):
    r = requests.post(
        f"{CPP_BASE}/route",
        json={"start": start, "end": end},
        timeout=10
    )
    r.raise_for_status()
    return r.json()

TOOLS = [
    {
        "type": "function",
        "function": {
            "name": "plan_route",
            "description": "Find a route between two indoor locations such as A125 and B923.",
            "parameters": {
                "type": "object",
                "properties": {
                    "start": {
                        "type": "string",
                        "description": "Start node, such as A125."
                    },
                    "end": {
                        "type": "string",
                        "description": "End node, such as B923."
                    }
                },
                "required": ["start", "end"]
            }
        }
    }
]

def call_local_tool(name, arguments):
    if name == "plan_route":
        return plan_route(arguments["start"], arguments["end"])
    return {"success": False, "error": f"Unknown tool: {name}"}

@app.route("/navigation_agent", methods=["POST"])
def navigation_agent():
    data = request.get_json(silent=True) or {}
    query = data.get("query", "").strip()

    if not query:
        return jsonify({
            "success": False,
            "final_message": "Empty query."
        }), 400

    messages = [
        {
            "role": "system",
            "content": (
                "You are an indoor navigation agent.\n"
                "Use tools whenever needed.\n"
                "Never invent tool results.\n"
                "If the user clearly provides a start and end location, call the tool directly.\n"
                "At the end, give a concise final answer with the distance and the path summary."
            )
        },
        {
            "role": "user",
            "content": query
        }
    ]

    actions = []

    try:
        while True:
            response = client.chat.completions.create(
                model=MODEL_NAME,
                messages=messages,
                tools=TOOLS,
                tool_choice="auto",
                temperature=0
            )

            message = response.choices[0].message

            if getattr(message, "tool_calls", None):
                messages.append(message)

                for tool_call in message.tool_calls:
                    tool_name = tool_call.function.name
                    arguments = json.loads(tool_call.function.arguments)

                    tool_result = call_local_tool(tool_name, arguments)

                    actions.append({
                        "tool": tool_name,
                        "arguments": arguments,
                        "result": tool_result
                    })

                    messages.append({
                        "role": "tool",
                        "tool_call_id": tool_call.id,
                        "content": json.dumps(tool_result, ensure_ascii=False)
                    })

                continue

            final_message = message.content if message.content else "No response."

            return jsonify({
                "success": True,
                "actions": actions,
                "final_message": final_message
            })

    except requests.RequestException as e:
        return jsonify({
            "success": False,
            "final_message": f"Tool server request failed: {str(e)}"
        }), 500
    except Exception as e:
        return jsonify({
            "success": False,
            "final_message": f"Agent failed: {str(e)}"
        }), 500

if __name__ == "__main__":
    app.run(port=5000, debug=True)