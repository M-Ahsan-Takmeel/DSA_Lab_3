#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Structure to represent a single bit node in the DLL
struct Node {
    int bit; // 0 or 1
    Node* prev;
    Node* next;

    Node(int b) {
        bit = b;
        prev = nullptr;
        next = nullptr;
    }
};

class BinaryNumber {
private:
    Node* head; // Points to Most Significant Bit (MSB)
    Node* tail; // Points to Least Significant Bit (LSB)

    // Helper to clear the list
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

public:
    BinaryNumber() {
        head = nullptr;
        tail = nullptr;
    }

    // Destructor
    ~BinaryNumber() {
        clear();
    }

    // 1. Store Binary Number (Padded to 8-bit blocks)
    void storeBinary(string binStr) {
        clear();

        // Ensure input contains only '0' or '1'
        for (char c : binStr) {
            if (c != '0' && c != '1') {
                cout << "\n[Error] Invalid binary string! Use only 0 and 1.\n";
                return;
            }
        }

        // Pad with leading zeros to make it a multiple of 8 bits
        int len = binStr.length();
        int remainder = len % 8;
        if (remainder != 0) {
            int padding = 8 - remainder;
            binStr = string(padding, '0') + binStr;
        }

        // Build the doubly linked list
        for (char c : binStr) {
            int bitVal = c - '0';
            Node* newNode = new Node(bitVal);
            if (head == nullptr) {
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
        cout << "\n[Success] Binary number stored in 8-bit grouped format.\n";
    }

    // Display the binary number with spaces every 8 bits
    void display() const {
        if (head == nullptr) {
            cout << "0";
            return;
        }
        Node* temp = head;
        int count = 0;
        while (temp != nullptr) {
            cout << temp->bit;
            count++;
            if (count % 8 == 0 && temp->next != nullptr) {
                cout << " "; // Group by 8 bits
            }
            temp = temp->next;
        }
    }

    // 2. 1's Complement
    void onesComplement() {
        Node* temp = head;
        while (temp != nullptr) {
            temp->bit = (temp->bit == 0) ? 1 : 0;
            temp = temp->next;
        }
    }

    // 3. 2's Complement (1's complement + 1)
    void twosComplement() {
        onesComplement();

        // Add 1 to the 1's complement result
        Node* temp = tail;
        int carry = 1;
        while (temp != nullptr && carry > 0) {
            int sum = temp->bit + carry;
            temp->bit = sum % 2;
            carry = sum / 2;
            temp = temp->prev;
        }
    }

    // Helper: Add two BinaryNumbers and return the result as a new BinaryNumber
    static BinaryNumber addBinary(const BinaryNumber& b1, const BinaryNumber& b2) {
        BinaryNumber result;
        Node* p1 = b1.tail;
        Node* p2 = b2.tail;
        int carry = 0;
        string resStr = "";

        while (p1 != nullptr || p2 != nullptr || carry > 0) {
            int sum = carry;
            if (p1 != nullptr) {
                sum += p1->bit;
                p1 = p1->prev;
            }
            if (p2 != nullptr) {
                sum += p2->bit;
                p2 = p2->prev;
            }

            carry = sum / 2;
            resStr = to_string(sum % 2) + resStr;
        }

        result.storeBinary(resStr);
        return result;
    }

    // Helper: Shift left by appending '0's (equivalent to multiplication by 2^n)
    void shiftLeft(int n) {
        if (head == nullptr) return;
        for (int i = 0; i < n; i++) {
            Node* newNode = new Node(0);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // 5. Binary Multiplication using repeated addition + shifting
    static BinaryNumber multiplyBinary(const BinaryNumber& b1, const BinaryNumber& b2) {
        BinaryNumber product;
        product.storeBinary("0");

        BinaryNumber tempB1 = b1;
        Node* p2 = b2.tail;
        int shiftCount = 0;

        while (p2 != nullptr) {
            if (p2->bit == 1) {
                BinaryNumber shifted = tempB1;
                // Shift according to position from LSB
                for (int i = 0; i < shiftCount; i++) {
                    shifted.shiftLeft(1);
                }
                product = addBinary(product, shifted);
            }
            p2 = p2->prev;
            shiftCount++;
        }

        return product;
    }

    // 6. Conversion to Decimal
    long long toDecimal() const {
        long long decimalVal = 0;
        Node* temp = head;
        while (temp != nullptr) {
            decimalVal = decimalVal * 2 + temp->bit;
            temp = temp->next;
        }
        return decimalVal;
    }
};

int main() {
    BinaryNumber num1, num2;
    string s1, s2;
    int choice;

    do {
        cout << "\n===================================\n";
        cout << "   BINARY ARITHMETIC USING DLL     \n";
        cout << "===================================\n";
        cout << "1. Store Binary Number\n";
        cout << "2. Compute 1's Complement\n";
        cout << "3. Compute 2's Complement\n";
        cout << "4. Binary Addition\n";
        cout << "5. Binary Multiplication\n";
        cout << "6. Convert to Decimal\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter binary number: ";
            cin >> s1;
            num1.storeBinary(s1);
            cout << "Stored format: ";
            num1.display();
            cout << "\n";
            break;

        case 2:
            cout << "Original: ";
            num1.display();
            num1.onesComplement();
            cout << "\n1's Complement: ";
            num1.display();
            cout << "\n";
            break;

        case 3:
            cout << "Original: ";
            num1.display();
            num1.twosComplement();
            cout << "\n2's Complement: ";
            num1.display();
            cout << "\n";
            break;

        case 4:
            cout << "Enter first binary number: ";
            cin >> s1;
            num1.storeBinary(s1);
            cout << "Enter second binary number: ";
            cin >> s2;
            num2.storeBinary(s2);

            {
                BinaryNumber sumResult = BinaryNumber::addBinary(num1, num2);
                cout << "Sum: ";
                sumResult.display();
                cout << " (Decimal: " << sumResult.toDecimal() << ")\n";
            }
            break;

        case 5:
            cout << "Enter first binary number: ";
            cin >> s1;
            num1.storeBinary(s1);
            cout << "Enter second binary number: ";
            cin >> s2;
            num2.storeBinary(s2);

            {
                BinaryNumber prodResult = BinaryNumber::multiplyBinary(num1, num2);
                cout << "Product: ";
                prodResult.display();
                cout << " (Decimal: " << prodResult.toDecimal() << ")\n";
            }
            break;

        case 6:
            cout << "Current Binary Number: ";
            num1.display();
            cout << "\nDecimal Equivalent: " << num1.toDecimal() << "\n";
            break;

        case 7:
            cout << "\nExiting program. Goodbye!\n";
            break;

        default:
            cout << "\n[Error] Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}