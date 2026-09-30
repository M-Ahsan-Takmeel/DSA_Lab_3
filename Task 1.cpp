#include <iostream>
#include <string>
using namespace std;

// Structure to represent a single song node
struct Song {
    int id;
    string name;
    string duration; // e.g., "3:45"
    Song* prev;
    Song* next;

    // Constructor to easily create a new song
    Song(int songId, string songName, string songDuration) {
        id = songId;
        name = songName;
        duration = songDuration;
        prev = nullptr;
        next = nullptr;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current; // Tracks the currently playing song

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // 1. Add Song - Insert at the end of the playlist
    void addSong(int id, string name, string duration) {
        Song* newSong = new Song(id, name, duration);

        if (head == nullptr) {
            head = tail = current = newSong;
        }
        else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "\n[Success] Song added successfully!\n";
    }

    // 2. Delete Song - Remove a song by its ID
    void deleteSong(int id) {
        if (head == nullptr) {
            cout << "\n[Error] Playlist is empty!\n";
            return;
        }

        Song* temp = head;
        while (temp != nullptr && temp->id != id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "\n[Error] Song with ID " << id << " not found!\n";
            return;
        }

        // If it's the currently playing song, shift current pointer
        if (current == temp) {
            if (temp->next != nullptr)
                current = temp->next;
            else if (temp->prev != nullptr)
                current = temp->prev;
            else
                current = nullptr;
        }

        // If it's the only node
        if (head == tail) {
            head = tail = nullptr;
        }
        // If it's the head node
        else if (temp == head) {
            head = head->next;
            head->prev = nullptr;
        }
        // If it's the tail node
        else if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        // If it's in the middle
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "\n[Success] Song deleted successfully!\n";
    }

    // 3. Display Playlist Forward
    void displayForward() {
        if (head == nullptr) {
            cout << "\n[Info] Playlist is empty.\n";
            return;
        }

        cout << "\n--- Playlist (Forward) ---\n";
        Song* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->id
                << " | Name: " << temp->name
                << " | Duration: " << temp->duration;
            if (temp == current) cout << "  <-- [Playing]";
            cout << endl;
            temp = temp->next;
        }
        cout << "--------------------------\n";
    }

    // 4. Display Playlist Backward
    void displayBackward() {
        if (tail == nullptr) {
            cout << "\n[Info] Playlist is empty.\n";
            return;
        }

        cout << "\n--- Playlist (Backward) ---\n";
        Song* temp = tail;
        while (temp != nullptr) {
            cout << "ID: " << temp->id
                << " | Name: " << temp->name
                << " | Duration: " << temp->duration;
            if (temp == current) cout << "  <-- [Playing]";
            cout << endl;
            temp = temp->prev;
        }
        cout << "---------------------------\n";
    }

    // 5. Search Song by ID
    void searchSong(int id) {
        Song* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "\n[Song Found]\n";
                cout << "ID: " << temp->id << "\n";
                cout << "Name: " << temp->name << "\n";
                cout << "Duration: " << temp->duration << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\n[Error] Song with ID " << id << " not found!\n";
    }

    // 6. Play Next Song
    void playNext() {
        if (current == nullptr) {
            cout << "\n[Error] No song is currently playing or playlist is empty.\n";
            return;
        }
        if (current->next != nullptr) {
            current = current->next;
            cout << "\nNow Playing: " << current->name << " (" << current->duration << ")\n";
        }
        else {
            cout << "\n[Info] You are at the last song of the playlist.\n";
        }
    }

    // Play Previous Song
    void playPrevious() {
        if (current == nullptr) {
            cout << "\n[Error] No song is currently playing or playlist is empty.\n";
            return;
        }
        if (current->prev != nullptr) {
            current = current->prev;
            cout << "\nNow Playing: " << current->name << " (" << current->duration << ")\n";
        }
        else {
            cout << "\n[Info] You are at the first song of the playlist.\n";
        }
    }

    // 7. Reverse Playlist In-Place using pointer manipulation
    void reversePlaylist() {
        if (head == nullptr || head == tail) {
            cout << "\n[Info] Playlist has 0 or 1 song. Cannot reverse.\n";
            return;
        }

        Song* currentPtr = head;
        Song* temp = nullptr;

        // Swap next and prev for all nodes
        while (currentPtr != nullptr) {
            temp = currentPtr->prev;
            currentPtr->prev = currentPtr->next;
            currentPtr->next = temp;
            currentPtr = currentPtr->prev; // moving to the old 'next' node
        }

        // Swap head and tail pointers
        temp = head;
        head = tail;
        tail = temp;

        cout << "\n[Success] Playlist reversed successfully!\n";
    }
};

int main() {
    Playlist myPlaylist;
    int choice, id;
    string name, duration;

    do {
        cout << "\n====== PLAYLIST MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist (Forward)\n";
        cout << "4. Display Playlist (Backward)\n";
        cout << "5. Search Song by ID\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Song ID: ";
            cin >> id;
            cin.ignore(); // clear input buffer
            cout << "Enter Song Name: ";
            getline(cin, name);
            cout << "Enter Duration (e.g., 3:30): ";
            cin >> duration;
            myPlaylist.addSong(id, name, duration);
            break;
        case 2:
            cout << "Enter Song ID to delete: ";
            cin >> id;
            myPlaylist.deleteSong(id);
            break;
        case 3:
            myPlaylist.displayForward();
            break;
        case 4:
            myPlaylist.displayBackward();
            break;
        case 5:
            cout << "Enter Song ID to search: ";
            cin >> id;
            myPlaylist.searchSong(id);
            break;
        case 6:
            myPlaylist.playNext();
            break;
        case 7:
            myPlaylist.playPrevious();
            break;
        case 8:
            myPlaylist.reversePlaylist();
            break;
        case 9:
            cout << "\nExiting program. Goodbye!\n";
            break;
        default:
            cout << "\n[Error] Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}