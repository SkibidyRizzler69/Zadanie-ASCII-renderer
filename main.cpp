#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

// Abstract Canvas class
class Canvas {
protected:
    int width, height;
public:
    Canvas(int w, int h) : width(w), height(h) {}
    virtual ~Canvas() = default;
    virtual void drawPixel(int x, int y, char symbol) = 0;
    virtual void display(std::ostream &os) const = 0;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// ASCII Canvas implementation
class ASCIICanvas : public Canvas {
private:
    std::vector<std::vector<char>> grid;
public:
    ASCIICanvas(int w, int h) : Canvas(w, h), grid(h, std::vector<char>(w, ' ')) {}

    void drawPixel(int x, int y, char symbol) override {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = symbol;
        }
    }

    void display(std::ostream &os) const override {
        for (const auto& row : grid) {
            for (char cell : row) {
                os << cell;
            }
            os << '\n';
        }
    }
};

// Abstract Figure class
class Figure {
protected:
    int x, y;
    char symbol;
public:
    Figure(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}
    virtual ~Figure() = default;
    virtual void draw(Canvas &canvas) const = 0;
};

// Rectangle class
class Rectangle : public Figure {
private:
    int width, height;
public:
    Rectangle(int x, int y, int width, int height, char symbol)
        : Figure(x, y, symbol), width(width), height(height) {}

    void draw(Canvas &canvas) const override {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                canvas.drawPixel(x + j, y + i, symbol);
            }
        }
    }
};

// Circle class
class Circle : public Figure {
private:
    int radius;
public:
    Circle(int x, int y, int radius, char symbol)
        : Figure(x, y, symbol), radius(radius) {}

    void draw(Canvas &canvas) const override {
        for (int i = -radius; i <= radius; ++i) {
            for (int j = -radius; j <= radius; ++j) {
                if (i * i + j * j <= radius * radius) {
                    canvas.drawPixel(x + j, y + i, symbol);
                }
            }
        }
    }
};

// Triangle class
class Triangle : public Figure {
private:
    int base, height;
public:
    Triangle(int x, int y, int base, int height, char symbol)
        : Figure(x, y, symbol), base(base), height(height) {}

    void draw(Canvas &canvas) const override {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j <= i * base / height; ++j) {
                canvas.drawPixel(x + j, y + i, symbol);
                canvas.drawPixel(x - j, y + i, symbol);
            }
        }
    }
};

// Function to parse configuration file
void parseConfig(const std::string& configFile,
                 int &canvasWidth, int &canvasHeight,
                 std::string &outputFile,
                 std::vector<std::unique_ptr<Figure>> &figures) {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open configuration file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        if (key == "canvas") {
            iss >> canvasWidth >> canvasHeight;
        } else if (key == "output") {
            iss >> outputFile;
        } else if (key == "figure") {
            std::string type;
            iss >> type;
            if (type == "rectangle") {
                int x, y, w, h;
                char symbol;
                iss >> x >> y >> w >> h >> symbol;
                figures.push_back(std::make_unique<Rectangle>(x, y, w, h, symbol));
            } else if (type == "circle") {
                int x, y, r;
                char symbol;
                iss >> x >> y >> r >> symbol;
                figures.push_back(std::make_unique<Circle>(x, y, r, symbol));
            } else if (type == "triangle") {
                int x, y, base, height;
                char symbol;
                iss >> x >> y >> base >> height >> symbol;
                figures.push_back(std::make_unique<Triangle>(x, y, base, height, symbol));
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config file>\n";
        return 1;
    }

    std::string configFile = argv[1];
    int canvasWidth = 0, canvasHeight = 0;
    std::string outputFile;
    std::vector<std::unique_ptr<Figure>> figures;

    try {
        parseConfig(configFile, canvasWidth, canvasHeight, outputFile, figures);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    ASCIICanvas canvas(canvasWidth, canvasHeight);

    for (const auto &figure : figures) {
        figure->draw(canvas);
    }

    std::ofstream ofs(outputFile);
    if (!ofs.is_open()) {
        std::cerr << "Cannot open output file.\n";
        return 1;
    }
    canvas.display(ofs);

    return 0;
}

