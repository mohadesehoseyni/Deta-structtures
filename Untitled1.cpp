#include <iostream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    int duration; // duration in seconds
    string genre;
    Song* next;
    Song* prev;
};

Song* head = nullptr;
Song* tail = nullptr;

void addSong(const string& title, const string& artist, int duration, const string& genre) {
    Song* newSong = new Song{ title, artist, duration, genre, nullptr, nullptr };
    if (!head) {
        head = tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
}

void removeSong(const string& title) {
    Song* temp = head;
    while (temp) {
        if (temp->title == title) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            if (temp == tail) tail = temp->prev;
            delete temp;
            return;
        }
        temp = temp->next;
    }
}

void removeSongsByArtist(const string& artist) {
    Song* temp = head;
    while (temp) {
        if (temp->artist == artist) {
            Song* toDelete = temp;
            temp = temp->next;
            removeSong(toDelete->title);
        } else {
            temp = temp->next;
        }
    }
}

void removeSongsByGenre(const string& genre) {
    Song* temp = head;
    while (temp) {
        if (temp->genre == genre) {
            Song* toDelete = temp;
            temp = temp->next;
            removeSong(toDelete->title);
        } else {
            temp = temp->next;
        }
    }
}

void displaySongs() {
    if (!head) {
        cout << "empty!" << endl;
        return;
    }
    Song* temp = head;
    while (temp) {
        cout << "Title: " << temp->title << ", Artist: " << temp->artist << ", Duration: " << temp->duration << "s, Genre: " << temp->genre << endl;
        temp = temp->next;
    }
}


void searchSong(const string& title) {
    Song* temp = head;
    while (temp) {
        if (temp->title == title) {
            cout << "Found: " << "Title: " << temp->title << ", Artist: " << temp->artist << ", Duration: " << temp->duration << "s, Genre: " << temp->genre << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Song not found." << endl;
}

void displayMenu() {
    cout << "\nWelcome to Music Playlist Manager!" << endl;
    cout << "Please choose an option:" << endl;
    cout << "1. Add a song" << endl;
    cout << "2. Remove a song" << endl;
    cout << "3. Remove songs by artist" << endl;
    cout << "4. Remove songs by genre" << endl;
    cout << "5. Display all songs" << endl;
    cout << "6. Search for a song" << endl;
    cout << "7. Exit" << endl;
}

int main() {
    int choice;
    string title, artist, genre;
    int duration;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter duration (seconds): ";
                cin >> duration;
                cout << "Enter genre: ";
                cin.ignore();
                getline(cin, genre);
                addSong(title, artist, duration, genre);
                break;
            case 2:
                cout << "Enter song title to remove: ";
                cin.ignore();
                getline(cin, title);
                removeSong(title);
                break;
            case 3:
                cout << "Enter artist name to remove all their songs: ";
                cin.ignore();
                getline(cin, artist);
                removeSongsByArtist(artist);
                break;
            case 4:
                cout << "Enter genre to remove all songs of that genre: ";
                cin.ignore();
                getline(cin, genre);
                removeSongsByGenre(genre);
                break;
            case 5:
                displaySongs();
                break;
            case 6:
                cout << "Enter song title to search: ";
                cin.ignore();
                getline(cin, title);
                searchSong(title);
                break;
            case 7:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }

    return 0;
}
