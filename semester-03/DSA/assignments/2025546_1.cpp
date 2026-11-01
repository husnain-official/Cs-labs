/*
    --- ASSIGNMENT:01 (CS-214) ---
    NAME:   M HUSNAIN AFZAL
    REG:    2025-546
    SEC:    CS-H2
*/
#include <iostream>
#include <string>

struct Packet
{
    int msg_number;
    int packet_number;
    char data;
    Packet *next;
};

class PacketList
{
    Packet *head = nullptr;
    Packet *tail = nullptr;
    int message_no{};

public:
    // Constructor/Destructor
    PacketList() = default;
    ~PacketList()
    {
        Packet *traversing_ptr = head;
        size_t packet_num{};
        // One by one go through each node, and free the memory, so there is no memory leaks.
        while (traversing_ptr != nullptr)
        {
            Packet *next = traversing_ptr->next;
            delete traversing_ptr;
            traversing_ptr = next;
            packet_num++;
        }
        std::cout << "\n\n[DESTRUCTOR]  |   Freed Total " << packet_num << " nodes from memory\n"
                  << std::endl;
    }
    // First we make a member to assign a new node to the end for easy appending.
    void push_back(Packet *pack)
    {
        // The linked list is empty.
        if (tail == nullptr)
        {
            head = pack;
            tail = pack;
            return;
        }
        // Else, attach at the end.
        tail->next = pack;
        tail = pack;
        return;
    }
    // Now make a member for decomposing the entire string into chars and making seperate packets.
    void make_packets(const std::string &message)
    {
        int count = 0;
        for (char c : message)
        {
            Packet *temp = new Packet{this->message_no, ++count, c, nullptr};
            this->push_back(temp);
        }
        return;
    }
    // Finally the function that will be called by user.
    void decompose_message(const std::string &message)
    {
        this->message_no++;
        this->make_packets(message);
        return;
    }
    // And also a member to display all packets in the linked list
    void display_list()
    {
        if (head == nullptr)
            return;
        std::cout << "\n\n---- Displaying all packets ----\n"
                  << std::endl;
        // Else show whats stored
        Packet *traversing_ptr = head;
        std::size_t packet_numbers{};
        while (traversing_ptr != nullptr)
        {
            // Show message
            std::cout << "The value of packet " << traversing_ptr->packet_number << " in message " << traversing_ptr->msg_number
                      << " is " << traversing_ptr->data << std::endl;
            ++packet_numbers;
            // Move to next packet
            traversing_ptr = traversing_ptr->next;
        }
        std::cout << "The total packets in the linked list are " << packet_numbers << std::endl;
        return;
    }
};
int main()
{
    // Demo main copied directly from Assignment pdf
    PacketList p;

    std::string message1 = "Hello";
    std::string message2 = "This";
    std::string message3 = "is";
    std::string message4 = "CS214";
    std::string message5 = "Assignment";
    p.decompose_message(message1);
    p.decompose_message(message2);
    p.decompose_message(message3);
    p.decompose_message(message4);
    p.decompose_message(message5);

    // Display all packets
    p.display_list();

    return 0;
}