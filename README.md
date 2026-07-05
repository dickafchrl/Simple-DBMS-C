# Mesin Ketik - Mini Database Engine

**Mesin Ketik** is a lightweight, command-line relational database engine prototype written in C. It uses a custom lexical analyzer and parser (modeled after tape-based machines) to interpret SQL-like query inputs and perform database operations on simple text-file tables.

## Features

- **SQL-Like Query Syntax**: Execute commands with syntax constraints, including mandatory trailing semicolons (`;`).
- **Interactive CLI**: Interactive query prompt (`query>`) with detailed help menu on startup.
- **CRUD Operations**:
  - `INSERT`: Adds a new record to a table (checks for primary key uniqueness and table capacity constraints).
  - `SHOW`: Displays all records in a table.
  - `UPDATE`: Modifies an existing record based on its primary key.
  - `DELETE`: Removes a record from a table and updates the file system.
- **Table Support**: Supports three default database tables:
  - `ITEMNAME` (stored in `ItemList.txt`)
  - `TYPE` (stored in `TypeList.txt`)
  - `PRICE` (stored in `PriceList.txt`)
- **Data Persistence**: Records are persisted in text format with a custom sentinel value (`#### #### #### ####`) marking the end of the data file.
- **Sorting & Searching**: Integrates a sequential search algorithm for primary key lookups and a bubble sort algorithm for record ordering.

---

## File Structure

- **[Library.h](file:///C:/Users/Advan/Documents/Magang/C/Mesin-Ketik/Library.h)**: Declares core structures (e.g., `dataName`), enumerations for commands and tables, global parsing variables, and function prototypes.
- **[Main.c](file:///C:/Users/Advan/Documents/Magang/C/Mesin-Ketik/Main.c)**: The entry point of the program. Initializes the CLI loop and reads user input ribbon-queries.
- **[Mesin.c](file:///C:/Users/Advan/Documents/Magang/C/Mesin-Ketik/Mesin.c)**: Implements database handlers, search/sort routines, file input/output routines, and parser state transitions (start, reset, increment, and eop checkers).
- **[ItemList.txt](file:///C:/Users/Advan/Documents/Magang/C/Mesin-Ketik/ItemList.txt)**: Default data store for the `ITEMNAME` table.

---

## Query Syntax Guide

Each query must end with a semicolon (`;`).

### 1. Show Table Content
Displays all active records from the target table.
```sql
SHOW <TABLE_NAME>;
```
Example:
```sql
SHOW ITEMNAME;
```

### 2. Insert Record
Inserts a new record. The primary key must be unique.
```sql
INSERT <TABLE_NAME> <PrimaryKey> <Attribute> <ForeignKey> <ForeignKeySecond>;
```
Example:
```sql
INSERT ITEMNAME I01 Baju Pakaian 50000;
```

### 3. Update Record
Modifies the attribute and foreign keys of a record identified by `<PrimaryKey>`.
```sql
UPDATE <TABLE_NAME> <PrimaryKey> <NewAttribute> <NewForeignKey> <NewForeignKeySecond>;
```
Example:
```sql
UPDATE ITEMNAME I01 BajuBaru Pakaian 60000;
```

### 4. Delete Record
Deletes the record corresponding to the specified `<PrimaryKey>`.
```sql
DELETE <TABLE_NAME> <PrimaryKey>;
```
Example:
```sql
DELETE ITEMNAME I01;
```

### 5. Exit Program
Terminates the CLI session.
```sql
exit;
```

---

## Database Record Schema

Every record uses the `dataName` structure:
- `PrimaryKey` (char[255]): The unique identifier for the record.
- `Attribute` (char[255]): Primary name or characteristic of the entry.
- `ForeignKey` (char[255]): Relational key link.
- `ForeignKeySecond` (char[255]): Secondary relational key or value.

---

## How to Build and Run

### Requirements
- GCC Compiler (or any standard C compiler)

### Compilation
Compile the project using your terminal:
```bash
gcc Main.c Mesin.c -o MesinKetik
```

### Execution
Run the compiled binary:
- **Windows**:
  ```cmd
  MesinKetik.exe
  ```
- **Linux/macOS**:
  ```bash
  ./MesinKetik
  ```
