#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

// Function to initialize the canvas with underscores
void initCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

// Function to display the canvas
void displayCanvas() {
    printf("\n--- CURRENT CANVAS ---\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
    printf("----------------------\n");
}

// Helper to safely set a pixel within bounds
void setPixel(int r, int c) {
    if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
        canvas[r][c] = '*';
    }
}

// Function to draw a line (Bresenham's basic logic or simple step)
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        setPixel(y1, x1); // using y as row, x as col
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Function to draw a rectangle
void drawRectangle(int r, int c, int height, int width) {
    for (int j = c; j < c + width; j++) {
        setPixel(r, j);                  // Top border
        setPixel(r + height - 1, j);     // Bottom border
    }
    for (int i = r; i < r + height; i++) {
        setPixel(i, c);                  // Left border
        setPixel(i, c + width - 1);      // Right border
    }
}

// Function to draw a triangle connecting 3 points
void drawTriangle(int r1, int c1, int r2, int c2, int r3, int c3) {
    drawLine(c1, r1, c2, r2);
    drawLine(c2, r2, c3, r3);
    drawLine(c3, r3, c1, r1);
}

// Function to draw a circle (Midpoint circle algorithm approximation)
void drawCircle(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (y >= x) {
        setPixel(yc + y, xc + x);
        setPixel(yc + y, xc - x);
        setPixel(yc - y, xc + x);
        setPixel(yc - y, xc - x);
        setPixel(yc + x, xc + y);
        setPixel(yc + x, xc - y);
        setPixel(yc - x, xc + y);
        setPixel(yc - x, xc - y);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

int main() {
    int choice;
    initCanvas();

    while (1) {
        printf("\n*** 2D GRAPHICS EDITOR MENU ***\n");
        printf("1. Display Canvas\n");
        printf("2. Add Line\n");
        printf("3. Add Rectangle\n");
        printf("4. Add Triangle\n");
        printf("5. Add Circle\n");
        printf("6. Delete/Clear Canvas\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1:
                displayCanvas();
                break;
            case 2: {
                int x1, y1, x2, y2;
                printf("Enter start coordinates (X Y, max 39 19): ");
                scanf("%d %d", &x1, &y1);
                printf("Enter end coordinates (X Y): ");
                scanf("%d %d", &x2, &y2);
                drawLine(x1, y1, x2, y2);
                printf("Line added successfully!\n");
                break;
            }
            case 3: {
                int r, c, h, w;
                printf("Enter top-left corner Row and Column (e.g., 2 5): ");
                scanf("%d %d", &r, &c);
                printf("Enter Height and Width: ");
                scanf("%d %d", &h, &w);
                drawRectangle(r, c, h, w);
                printf("Rectangle added successfully!\n");
                break;
            }
            case 4: {
                int r1, c1, r2, c2, r3, c3;
                printf("Enter Point 1 (Row Col): ");
                scanf("%d %d", &r1, &c1);
                printf("Enter Point 2 (Row Col): ");
                scanf("%d %d", &r2, &c2);
                printf("Enter Point 3 (Row Col): ");
                scanf("%d %d", &r3, &c3);
                drawTriangle(r1, c1, r2, c2, r3, c3);
                printf("Triangle added successfully!\n");
                break;
            }
            case 5: {
                int xc, yc, rad;
                printf("Enter center coordinates (X Y): ");
                scanf("%d %d", &xc, &yc);
                printf("Enter radius: ");
                scanf("%d %d", &rad);
                drawCircle(xc, yc, rad);
                printf("Circle added successfully!\n");
                break;
            }
            case 6:
                initCanvas();
                printf("Canvas cleared (Objects deleted)!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
