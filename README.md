Movie Ticket Booking System with AVL Tree
Overview

This project implements a Movie Ticket Booking System using an AVL (Adelson-Velsky and Landis) tree data structure in C. The AVL tree ensures efficient insertion, deletion, and retrieval of movie shows while maintaining a balanced tree structure.
Features

    Show Management: Users can create, add, and delete movie shows.
    Seat Booking: Allows users to book seats for a particular show.
    Seat Display: Displays the availability of seats for a specific show.
    Invoice Generation: Generates an invoice for booked tickets, including customer details.
    File Handling: Reads and writes show data to a file for persistence.

AVL Tree Implementation

    Tree Rotation: Implements left and right rotations to maintain AVL tree balance during insertion and deletion operations.
    Balanced Tree: Ensures the AVL tree remains balanced to provide optimal performance for operations like insertion, deletion, and searching.

Code Structure

    Node Structure: Defines structures for both AVL tree nodes and linked list nodes to manage seat status.
    Tree Operations: Includes functions for insertion, deletion, and traversal of the AVL tree.
    Seat Booking: Implements seat booking functionality along with seat status management.
    File Handling: Reads and writes show data to/from a file for persistent storage.

How to Use

    Compile: Compile the code using a C compiler.
    Run: Execute the compiled program.
    Choose Options: Follow the prompts to perform various actions such as creating shows, booking seats, etc.
    Exit: Terminate the program when finished.

Further Improvements

    User Interface: Enhance the user interface for better interaction.
    Error Handling: Implement robust error handling mechanisms.
    Database Integration: Integrate with a database for efficient data management.
    Security: Implement security features to protect user data.

Conclusion

This Movie Ticket Booking System provides a basic framework for managing movie shows and seat bookings using an AVL tree data structure. It can serve as a foundation for more advanced ticket booking systems with additional features and enhancements.
