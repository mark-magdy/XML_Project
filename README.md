XML Parser and Social Network Analysis

A comprehensive solution for processing, validating, and analyzing XML-based datasets with practical applications in social network analytics.
Table of Contents

    Overview
    Features
    Getting Started
        Installation
        Usage
    Core Functionalities
        XML Validation
        Graph-Based Analysis
        Post Search
    Time and Space Complexity
    Technologies Used
    Contributing
    License

Overview

This project provides an efficient and modular XML parser designed to handle large datasets while offering tools for graph-based social network analysis. Equipped with CLI and GUI interfaces, it caters to both technical and non-technical users, making it a versatile tool for data engineers, researchers, and developers.
Features

    XML Validation: Validates XML files for proper syntax and tag matching.
    Graph-Based Analysis: Models social network relationships using graph data structures.
    Post Search: Allows searching posts by ID, date, word, or topic.
    Data Visualization: Displays graph-based networks with nodes and edges.
    Compression: Reduces XML file size using Huffman encoding.
    User-Friendly Interfaces: Includes both CLI and GUI for flexibility.
Core Functionalities
XML Validation

    Checks for mismatched tags, missing attributes, and structural inconsistencies.
    Time Complexity: O(n), where n is the size of the XML file.

Graph-Based Analysis

    Constructs directed graphs for relationships between users.
    Supports common operations like finding mutual connections, shortest paths, and more.

Post Search

    Search posts using various criteria:
        By ID: Direct lookup for a specific post ID.
        By Date: Retrieve posts from a specific date range.
        By Word: Search for posts containing a specific keyword.
        By Topic: Retrieve posts associated with a specific topic.
Technologies Used

    Programming Language: C++
    Graph Library: Boost or custom implementation
    GUI Framework: Qt / Dear ImGui
    Compression: LZ77 Encoding
