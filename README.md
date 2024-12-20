# Thoughtful AI Agent

A simple customer support AI agent built using [Crow](https://github.com/CrowCpp/Crow) for C++ 
## Features
- Responds to user questions using predefined answers.
- Supports fallback responses for unknown queries.

## How to Run

### C++ (Using Crow)
1. **Install Dependencies**:
    - Install [Crow](https://github.com/CrowCpp/Crow).
    - Install [jsoncpp](https://github.com/open-source-parsers/jsoncpp).

2. **Compile and Run**:
    ```bash
    g++ -std=c++17 main.cpp -o server -lcrow -ljsoncpp
    ./server
    ```

3. Test:
   - Send a POST request to `http://localhost:8080/ask` with a JSON body:
     ```json
     {
       "question": "Tell me about Thoughtful AI's Agents."
     }
     ```
