#include "vehicle.cpp"
#include <vector>

class Board {
private:
    int rows, cols;
    std::vector<std::vector<Vehicle>> grid;

public:
    Board(int numRows, int numCols) : rows(numRows), cols(numCols) {
        grid.resize(rows);
        for (int i = 0; i < rows; ++i) {
            grid[i].resize(cols);
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    bool isPositionEmpty(Vector2 pos) const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!grid[i][j].getPosition().Equals(pos)) {
                    Rectangle bounds = grid[i][j].getBounds();
                    if (CheckCollisionPointRec(pos, bounds)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void addVehicle(const Vehicle& vehicle) {
        Vector2 pos = vehicle.getPosition();
        int row = pos.y / vehicle.getBounds().height;
        int col = pos.x / vehicle.getBounds().width;
        grid[row][col] = vehicle;
    }

    void draw() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!grid[i][j].getPosition().Equals({0, 0})) {
                    grid[i][j].draw();
                }
            }
        }
    }
};
