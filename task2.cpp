#include <iostream>
#include <cmath> // для pow

// Абстрактний базовий клас
class Progression {
protected:
    double a0;  // перший член прогресії
    double step;  // крок (різниця або знаменник)
public:
    Progression(double a0_val, double step_val) : a0(a0_val), step(step_val) {}

    // Віртуальна функція для обчислення суми
    virtual double sum(int n) const = 0;

    virtual ~Progression() {}
};

// Арифметична прогресія
class ArithmeticProgression : public Progression {
public:
    ArithmeticProgression(double a0_val, double d) : Progression(a0_val, d) {}

    double sum(int n) const override {
        double an = a0 + step * n;  // останній член
        return (n + 1) * (a0 + an) / 2;
    }
};

// Геометрична прогресія
class GeometricProgression : public Progression {
public:
    GeometricProgression(double a0_val, double r) : Progression(a0_val, r) {}

    double sum(int n) const override {
        double an = a0 * std::pow(step, n + 1);
        if (step == 1)  // уникаємо ділення на 0
            return a0 * (n + 1);
        return (a0 - an) / (1 - step);
    }
};

int main() {
    ArithmeticProgression ap(1.0, 2.0); // a0 = 1, d = 2
    GeometricProgression gp(1.0, 2.0);  // a0 = 1, r = 2

    int n = 4; // n = кількість елементів - 1 (тобто 5 членів: j=0..4)

    std::cout << "Сума арифметичної прогресії (n = " << n << "): " << ap.sum(n) << "\n";
    std::cout << "Сума геометричної прогресії (n = " << n << "): " << gp.sum(n) << "\n";

    return 0;
}
