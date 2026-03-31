import requests

AGENT_URL = "http://127.0.0.1:5000/navigation_agent"

def main():
    print("Indoor Navigation CLI (输入 q 退出)\n")

    while True:
        query = input(">>> ").strip()

        if query.lower() == "q":
            break

        try:
            response = requests.post(
                AGENT_URL,
                json={"query": query},
                timeout=30
            )

            data = response.json()

            if data.get("success"):
                print("\n" + data.get("final_message", ""))
            else:
                print("\n[ERROR]", data.get("final_message", ""))

        except Exception as e:
            print(f"\n请求失败: {e}")

if __name__ == "__main__":
    main()