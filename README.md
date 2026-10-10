# Create a Store Inventory GUI Application with C++ and Qt

**Companion source code for the 2026 course update**  
**Instructor:** Dr. John Baugh  
**Technologies:** C++, Qt 6, Qt Widgets, Qt Creator, Qt Designer, and CMake

## About the Course

This repository accompanies my Udemy course, **[Create a Store Inventory GUI Application with C++ and Qt](https://www.udemy.com/course/create-a-store-inventory-gui-application-with-cpp-and-qt/)**.

This hands-on course walks through the development of a desktop store inventory application using modern C++ and the Qt framework. You'll begin with the fundamentals of Qt development, then apply those ideas to build a working graphical application with forms, tables, dialogs, event handling, and file persistence.

The emphasis is on understanding **how the pieces of a Qt application fit together**, not just copying code: organizing C++ classes, designing user interfaces, connecting signals to slots, validating input, and moving data between the interface and an in-memory model.

**[View the Complete Course on Udemy](https://www.udemy.com/course/create-a-store-inventory-gui-application-with-cpp-and-qt/)**

## What you'll build

The **Store Inventory App** lets you:

- Add, edit, and delete products using a reusable dialog.
- Track each product's name, SKU, quantity, price, and optional image path.
- Display products in a table and view details for a selected product.
- Calculate the total value of individual products (`quantity × price`).
- Search products by name or SKU.
- Create a new inventory, open an existing one, and save inventory data as JSON.
- Validate product information and provide feedback through dialogs and status messages.

Product images are referenced by file path; they are **not embedded in the JSON data**. If you move an inventory file to another machine, you may need to select or restore the corresponding images.

## Course progression

**Section 1 — Qt Foundations: Widgets, Products, and JSON**  
Get comfortable with Qt Creator, Qt Designer, CMake, signals and slots, the `Product` class, Qt containers such as `QVector<Product>`, and JSON serialization through a smaller Product Data Utility exercise.

**Section 2 — Building the Store Inventory GUI App**  
Create the full `StoreInventoryApp` interface, introduce a reusable `ProductDialog`, implement product operations, connect tables and detail views, add images and JSON persistence, then refine the application with validation, search, and deployment concepts.

**About this repository:** It contains the Store Inventory GUI application from Section 2. It represents the application source as published here, rather than a separate snapshot for every lecture. Follow the course videos when building the project incrementally.

## Requirements

- **Qt 6.5 or later**, with the Qt Widgets module.
- **Qt Creator** and a configured **Desktop Qt kit** (compiler and matching Qt installation).
- **CMake 3.19 or later** (Qt Creator can manage CMake configuration and builds).
- A supported desktop development environment on Windows, macOS, or Linux.

The course demonstrations use Qt 6 and a CMake-based Qt Widgets project. Using a similar Qt Creator kit will make the lessons easier to follow.

## Getting started

1. **Get the code.** Clone this repository, or use GitHub's **Code → Download ZIP** option:

   `git clone https://github.com/profjpbaugh/cpp-qt-store-inventory-gui.git`

2. **Open the project in Qt Creator.** Choose **File → Open File or Project**, navigate to the downloaded folder, and select `CMakeLists.txt`.
3. **Configure the project.** Select a suitable Desktop Qt kit when Qt Creator prompts you to configure it.
4. **Build and run.** Use Qt Creator's **Run** button (or build first, then run).
5. **Try the sample data.** Use the app's **Open** command to select `inventory.json` or `inventory2.json` from the repository, if desired.

If Qt Creator cannot find Qt, check that the chosen kit points to a Qt 6 installation with the Widgets component and a compatible compiler.

## Repository guide

| File | Purpose |
| --- | --- |
| `CMakeLists.txt` | CMake configuration for the Qt Widgets application. |
| `main.cpp` | Application entry point. |
| `mainwindow.h`, `mainwindow.cpp`, `mainwindow.ui` | Main window behavior and user interface. |
| `Product.h`, `Product.cpp` | Product data model, calculations, and JSON conversion. |
| `ProductDialog.h`, `ProductDialog.cpp`, `ProductDialog.ui` | Dialog for entering and editing product information. |
| `inventory.json`, `inventory2.json` | Example inventory data files. |

The `.ui` files are editable using Qt Designer inside Qt Creator. Build output and machine-specific IDE settings generally should not be committed to the repository.

## Concepts practiced

- C++ classes, constructors, getters/setters, and separating declarations from implementations.
- Qt's event-driven programming model using **signals and slots**.
- Visual interface design with **Qt Widgets** and **Qt Designer**.
- Dialogs, tables, selection, form validation, and user feedback.
- Managing application data with **`QVector<Product>`**.
- Serialization and file I/O with **Qt JSON classes**.
- Configuring, building, and preparing a desktop application with **CMake and Qt Creator**.

## Notes for students

This is a **learning project**, designed to illustrate practical desktop development techniques. The source may differ from what appears at a particular point in a lesson because the repository reflects a later state of the application. For the best experience, build along with the lectures and use this code to review or troubleshoot.

**Instructor:** Dr. John Baugh  
**Repository:** https://github.com/profjpbaugh/cpp-qt-store-inventory-gui
