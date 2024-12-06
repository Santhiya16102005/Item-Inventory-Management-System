#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define a structure to represent an item
typedef struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
    struct Item* left;
    struct Item* right;
} Item;

// Function to create a new item
Item* createItem(int id, const char* name, int quantity, float price) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->left = NULL;
    newItem->right = NULL;
    return newItem;
}

// Function to insert a new item into the BST
Item* insertItem(Item* root, int id, const char* name, int quantity, float price) {
    if (root == NULL) {
        return createItem(id, name, quantity, price);
    }
    if (id < root->id) {
        root->left = insertItem(root->left, id, name, quantity, price);
    } else if (id > root->id) {
        root->right = insertItem(root->right, id, name, quantity, price);
    }
    return root;
}

// Function to search for an item by its id in the BST
Item* searchItem(Item* root, int id) {
    if (root == NULL || root->id == id) {
        return root;
    }
    if (id < root->id) {
        return searchItem(root->left, id);
    }
    return searchItem(root->right, id);
}

// Function to display all items in the BST (inorder traversal)
void displayInventory(Item* root) {
    if (root != NULL) {
        displayInventory(root->left);
        printf("ID: %d, Name: %s, Quantity: %d, Price: %.2f\n", root->id, root->name, root->quantity, root->price);
        displayInventory(root->right);
    }
}

int main() {
    Item* root = NULL;

    // Insert predefined items into the BST
    root = insertItem(root, 1, "Laptop", 10, 1000.00);
    root = insertItem(root, 2, "Phone", 20, 500.00);
    root = insertItem(root, 3, "Tablet", 15, 700.00);
    root = insertItem(root, 4, "Headphones", 50, 100.00);
    root = insertItem(root, 5, "Charger", 100, 20.00);

    printf("Available Items:\n");
    displayInventory(root);

    int itemId;
    printf("\nEnter the Item ID to view details: ");
    scanf("%d", &itemId);

    Item* foundItem = searchItem(root, itemId);
    if (foundItem != NULL) {
        printf("\nItem Details:\n");
        printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n",
               foundItem->id, foundItem->name, foundItem->quantity, foundItem->price);
    } else {
        printf("\nItem with ID %d not found.\n", itemId);
    }

    return 0;
}