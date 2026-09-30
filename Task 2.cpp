#include <iostream>

using namespace std;

// Structure to represent a person
struct Node {
    int id;
    Node* next;
};

// Function to create a circular linked list of N people
Node* createCircle(int n) {
    Node* head = new Node{ 1, nullptr };
    Node* curr = head;

    for (int i = 2; i <= n; i++) {
        curr->next = new Node{ i, nullptr };
        curr = curr->next;
    }

    // Make it circular by pointing the last node back to head
    curr->next = head;
    return head;
}

// Function to run the elimination game
void simulateJosephus(int n, int k) {
    if (n <= 0 || k <= 0) {
        cout << "N and k must be greater than 0!\n";
        return;
    }

    // Step 1: Create the circle
    Node* head = createCircle(n);

    Node* curr = head;
    Node* prev = nullptr;

    // Find the last node to set up 'prev' correctly
    prev = head;
    while (prev->next != head) {
        prev = prev->next;
    }

    cout << "\n--- Josephus Problem Simulation ---\n";
    cout << "Elimination Order: ";

    // Step 2: Keep eliminating until only one person remains
    while (curr->next != curr) {
        // Count k-1 steps to find the k-th person to eliminate
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }

        // Print the eliminated person
        cout << curr->id << " ";

        // Remove the person from the linked list
        prev->next = curr->next;
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }

    // Step 3: Print the winner
    cout << "\n-----------------------------------\n";
    cout << "Survivor: Person ID " << curr->id << " wins!\n";
    cout << "-----------------------------------\n";

    // Clean up the last remaining node
    delete curr;
}

int main() {
    int n, k;

    cout << "Enter total number of people (N): ";
    cin >> n;
    cout << "Enter elimination step count (k): ";
    cin >> k;

    simulateJosephus(n, k);

    return 0;
}