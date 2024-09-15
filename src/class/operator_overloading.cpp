#include <iostream>
#include <istream>
#include <random>

class money {
private:
  int m_size = 10;

public:
  int m_value;
  int *data;

  money(int value = 10) : m_value(value) {
    std::cout << "Constructor money with m_value: " << m_value << std::endl;

    data = new int[m_size];

    int upperBound = 20;
    int lowerBound = 0;
    int numberOfRandomNumbers = m_size;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(lowerBound, upperBound);

    for (int n = 0; n < numberOfRandomNumbers; ++n)
      data[n] = dis(gen);
  }

  ~money() {
    std::cout << "Destructor money with value: " << m_value << std::endl;
    delete[] data;
  }

  double operator()() { return m_value; }

  friend money operator-(const money &t1, int m_value);
  friend std::ostream &operator<<(std::ostream &os, const money &t);
  friend std::istream &operator>>(std::istream &is, const money &t);

  bool operator<(const money &other) const { return m_value < other.m_value; }

  money operator-(const money &other) {
    m_value - other.m_value;
    return *this;
  }

  // Copy constructor for deep copy
  money(const money &other) : m_value(other.m_value), m_size(other.m_size) {
    data = new int[m_size];
    std::copy(other.data, other.data + m_size, data);
  }

  // Copy assignment operator for deep copy
  money &operator=(const money &other) {
    if (this != &other) {
      delete[] data;

      m_value = other.m_value;
      m_size = other.m_size;
      data = new int[m_size];
      std::copy(other.data, other.data + m_size, data);
    }
    return *this;
  }
};

money operator-(const money &t1, int m_value) {
  return money(t1.m_value - m_value);
}

std::ostream &operator<<(std::ostream &os, const money &t) {
  for (int i = 0; i < t.m_size; i++)
    os << t.data[i] << " ";
  return os;
}

std::istream &operator>>(std::istream &is, money &t) {
  is >> t.m_value;
  return is;
}

struct cell {
  int index;
  float cost;
  //  bool operator<(const cell &otherside) { return cost < otherside.cost; }
};

bool operator<(const cell &lhs, const cell &rhs) { return lhs.cost < rhs.cost; }

int main() {

  money money3;
  std::cout << "Enter the size: " << std::endl;

  // getchar();
  std::cin >> money3;
  std::cout << "The operator >> gives you:" << money3 << std::endl;

  money money1(7), money2(3);
  std::cout << "The operator - gives you:" << std::endl;
  std::cout << money2 - money1 << std::endl;
  std::cout << "The operator ()  gives you:\n" << money1() << std::endl;
  std::cout << "The operator () << gives you:\n" << money1 << std::endl;
}
