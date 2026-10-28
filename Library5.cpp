
#include <iostream>
#include <string>
#include <limits>
#include <utility>
using namespace std;

// Book Node
struct BookNode
{
    int bookID;
    string title;
    BookNode* next;
};

// Linked List Class
class LinkedList
{
private:
    BookNode* head;
    int count;

    // Get node at a specific index
    BookNode* GetNodeAt(int index)
    {
        BookNode* current = head;

        for (int i = 0; i < index && current != nullptr; i++)
        {
            current = current->next;
        }

        return current;
    }

    // Swap book data
    void CopyBookData(BookNode* a, BookNode* b)
    {
        swap(a->bookID, b->bookID);
        swap(a->title, b->title);
    }

public:
    // Constructor
    LinkedList()
    {
        head = nullptr;
        count = 0;
    }

    // Check if list is empty
    bool IsEmpty()
    {
        return head == nullptr;
    }

    bool IsNotEmpty()
    {
        return head != nullptr;
    }

    // Insert at head
    void Insert(BookNode* book)
    {
        if (book == nullptr)
            return;

        book->next = head;
        head = book;
        count++;
    }

    // Remove from head
    BookNode* Remove()
    {
        if (IsEmpty())
            return nullptr;

        BookNode* book = head;
        head = head->next;
        book->next = nullptr;
        count--;

        return book;
    }

    // Insert at index
    void InsertAt(BookNode* book, int index)
    {
        if (book == nullptr)
            return;

        if (index < 0)
            index = 0;

        if (index > count)
            index = count;

        if (index == 0)
        {
            Insert(book);
            return;
        }

        BookNode* previous = GetNodeAt(index - 1);

        book->next = previous->next;
        previous->next = book;
        count++;
    }

    // Remove at index
    BookNode* RemoveAt(int index)
    {
        if (IsEmpty())
            return nullptr;

        if (index < 0 || index >= count)
            return nullptr;

        if (index == 0)
            return Remove();

        BookNode* previous = GetNodeAt(index - 1);
        BookNode* book = previous->next;

        previous->next = book->next;
        book->next = nullptr;
        count--;

        return book;
    }

    // Swap two indexes
    void Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= count ||
            index2 < 0 || index2 >= count)
        {
            cout << "Invalid index!\n";
            return;
        }

        if (index1 == index2)
        {
            cout << "Both indexes are the same.\n";
            return;
        }

        BookNode* first = GetNodeAt(index1);
        BookNode* second = GetNodeAt(index2);

        CopyBookData(first, second);

        cout << "Books swapped successfully!\n";
    }

    // Sort by book ID
    void Sort()
    {
        for (BookNode* i = head; i != nullptr; i = i->next)
        {
            for (BookNode* j = i->next; j != nullptr; j = j->next)
            {
                if (i->bookID > j->bookID)
                {
                    CopyBookData(i, j);
                }
            }
        }

        cout << "Books sorted by ID!\n";
    }

    // Reverse list
    void Reverse()
    {
        BookNode* previous = nullptr;
        BookNode* current = head;
        BookNode* next = nullptr;

        while (current != nullptr)
        {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        head = previous;

        cout << "Collection reversed successfully!\n";
    }

    // Display books
    void Print()
    {
        if (IsEmpty())
        {
            cout << "\nCollection is empty!\n";
            return;
        }

        BookNode* current = head;
        int index = 0;

        cout << "\nIndex\tBook ID\tTitle\n";
        cout << "----------------------------------------\n";

        while (current != nullptr)
        {
            cout << index << "\t"
                 << current->bookID << "\t"
                 << current->title << endl;

            current = current->next;
            index++;
        }

        cout << "Total books: " << count << endl;
    }

    // Get total number of books
    int GetCount()
    {
        return count;
    }

    // Destructor
    ~LinkedList()
    {
        while (!IsEmpty())
        {
            delete Remove();
        }
    }
};

// Create a new book
BookNode* CreateBook(int id, string title)
{
    BookNode* book = new BookNode;

    book->bookID = id;
    book->title = title;
    book->next = nullptr;

    return book;
}

// Main function
int main()
{
    LinkedList library;
    int choice, id, index, index1, index2;
    string title;
    BookNode* removed;

    // Initial books
    library.InsertAt(CreateBook(103, "Operating Systems"), 0);
    library.InsertAt(CreateBook(101, "Data Structures"), 1);
    library.InsertAt(CreateBook(105, "Computer Networks"), 2);
    library.InsertAt(CreateBook(102, "Database Systems"), 3);
    library.InsertAt(CreateBook(104, "Software Engineering"), 4);

    do
    {
        cout << "\n====================================\n";
        cout << " LIBRARY BOOK COLLECTION SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Display All Books\n";
        cout << "2. Insert Book at Head\n";
        cout << "3. Remove Book from Head\n";
        cout << "4. Insert Book at Index\n";
        cout << "5. Remove Book at Index\n";
        cout << "6. Swap Books\n";
        cout << "7. Sort Books by ID\n";
        cout << "8. Reverse Book Collection\n";
        cout << "9. Check Collection Status\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            library.Print();
            break;

        case 2:
            cout << "Enter Book ID: ";
            cin >> id;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Book Title: ";
            getline(cin, title);

            library.Insert(CreateBook(id, title));
            cout << "Book inserted at head successfully!\n";
            break;

        case 3:
            removed = library.Remove();

            if (removed != nullptr)
            {
                cout << "Removed book: "
                     << removed->bookID << " - "
                     << removed->title << endl;
                delete removed;
            }
            else
            {
                cout << "Collection is empty!\n";
            }
            break;

        case 4:
            cout << "Enter Book ID: ";
            cin >> id;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Book Title: ";
            getline(cin, title);

            cout << "Enter index (starting from 0): ";
            cin >> index;

            if (index < 0 || index > library.GetCount())
            {
                cout << "Invalid index! Valid indexes are 0 to "
                     << library.GetCount() << ".\n";
                break;
            }

            library.InsertAt(CreateBook(id, title), index);
            cout << "Book inserted successfully!\n";
            break;

        case 5:
            cout << "Enter index to remove: ";
            cin >> index;

            removed = library.RemoveAt(index);

            if (removed != nullptr)
            {
                cout << "Removed book: "
                     << removed->bookID << " - "
                     << removed->title << endl;
                delete removed;
            }
            else
            {
                cout << "Invalid index or collection is empty!\n";
            }
            break;

        case 6:
            cout << "Enter first index: ";
            cin >> index1;

            cout << "Enter second index: ";
            cin >> index2;

            library.Swap(index1, index2);
            break;

        case 7:
            library.Sort();
            break;

        case 8:
            library.Reverse();
            break;

        case 9:
            if (library.IsEmpty())
            {
                cout << "Collection is empty.\n";
            }
            else
            {
                cout << "Collection is not empty.\n";
                cout << "Total books: "
                     << library.GetCount() << endl;
            }
            break;

        case 10:
            cout << "Exiting Library System. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice! Please select 1-10.\n";
        }

    } while (choice != 10);

    return 0;
}
