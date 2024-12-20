#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <json/json.h>
#include "crow.h"

using namespace std;

// Define the predefined dataset for questions and answers.
vector<pair<string, string>> data = {
    {"What does the eligibility verification agent (EVA) do?", "EVA automates the process of verifying a patient’s eligibility and benefits information in real-time, eliminating manual data entry errors and reducing claim rejections."},
    {"What does the claims processing agent (CAM) do?", "CAM streamlines the submission and management of claims, improving accuracy, reducing manual intervention, and accelerating reimbursements."},
    {"How does the payment posting agent (PHIL) work?", "PHIL automates the posting of payments to patient accounts, ensuring fast, accurate reconciliation of payments and reducing administrative burden."},
    {"Tell me about Thoughtful AI's Agents.", "Thoughtful AI provides a suite of AI-powered automation agents designed to streamline healthcare processes. These include Eligibility Verification (EVA), Claims Processing (CAM), and Payment Posting (PHIL), among others."},
    {"What are the benefits of using Thoughtful AI's agents?", "Using Thoughtful AI's Agents can significantly reduce administrative costs, improve operational efficiency, and reduce errors in critical processes like claims management and payment posting."}
};

string find_best_match(const string& user_question) {
    double best_score = 0.0;
    string best_answer = "I'm sorry, I don't have an answer to that question. Please contact support for more assistance.";

    for (const auto& [question, answer] : data) {
        int matches = 0;
        for (size_t i = 0; i < question.size(); ++i) {
            if (i < user_question.size() && question[i] == user_question[i]) {
                ++matches;
            }
        }

        double similarity = static_cast<double>(matches) / max(question.size(), user_question.size());
        if (similarity > best_score) {
            best_score = similarity;
            best_answer = answer;
        }
    }
    return best_answer;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/ask").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body["question"].s()) {
            return crow::response(400, "{\"error\": \"No question provided.\"}");
        }
        string user_question = body["question"].s();
        string response = find_best_match(user_question);

        crow::json::wvalue json_resp;
        json_resp["answer"] = response;
        return crow::response(json_resp);
    });

    app.port(8080).multithreaded().run();
    return 0;
}
