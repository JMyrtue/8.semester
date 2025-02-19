/// Created by Marius Mikucionis <marius@cs.aau.dk>
/**
 * Definitions/implementation of some number_series methods
 */

#include "number_series.hpp"

#include <random>

namespace data_series
{
    int number_series::get_min() const { return min; }
    int number_series::get_max() const { return max; }
    int number_series::amplitude() const { return max - min; }
    bool number_series::operator<(const number_series& other) const { return amplitude() < other.amplitude(); }

    long int number_series::size() const { return data.size(); }
    void number_series::add_value(const int num)
    {
        data.push_back(num);
        if(data.size() == 1) {
            max = num;
            min = num;
        } else if (num > max) {
            max = num;
        } else if (num < min) {
            min = num;
        }
    }

    number_series& number_series::operator+=(const number_series &other)
    {
        if (size() >= other.size()) {
            for (int i = 0; i < other.size(); i++) {
                data[i] += other.data[i];
            }
        } else {
            int i = 0;
            while (i < size()) {
                data[i] += other.data[i];
                i++;
            }
            while (i < other.size()) {
                add_value(other.data[i]);
                i++;
            }
        }
        return *this;
    }

    number_series number_series::operator+(const number_series &other)
    {
        number_series temp;
        if (size() >= other.size()) {
            int i = 0;
            while (i < other.size()) {
                temp.add_value(data[i] + other.data[i]);
                i++;
            }
            while (i < size()) {
                temp.add_value(data[i]);
                i++;
            }
        } else {
            int i = 0;
            while (i < size()) {
                temp.add_value(data[i] + other.data[i]);
                i++;
            }
            while (i < other.size()) {
                temp.add_value(other.data[i]);
                i++;
            }
        }
        return temp;
    }

    number_series::number_series() = default;
    number_series::number_series(std::initializer_list<int> list)
    {
        for (auto num : list) {
            add_value(num);
        }
    }
    number_series::number_series(std::vector<int> list)
    {
        for (auto num : list) {
            add_value(num);
        }
    }

    number_series number_series::make_random(int amount)
    {
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> distrib(0, 10);

        std::vector<int> temp;
        for (int i = 0; i < amount; ++i) {
            temp.push_back(distrib(gen));
        }
        return number_series{temp};
    }



    // Wrap functionality hereunder:
    number_series_wrap::number_series_wrap() = default;

    void number_series_wrap::add_value (int num) {
        data->add_value(num);
    }

    number_series_wrap::number_series_wrap(std::initializer_list<int> list)
    {
        for (auto num : list) {
            add_value(num);
        }
    }
    number_series_wrap::number_series_wrap(std::vector<int> list)
    {
        for (const auto num : list) {
            add_value(num);
        }
    }

    number_series_wrap::number_series_wrap(number_series series)
    {
        data = std::make_unique<number_series>(series);
    }

    number_series_wrap::number_series_wrap(const number_series_wrap& other)
        : data(std::make_unique<number_series>(*other.data)) {}

    number_series_wrap& number_series_wrap::operator=(const number_series_wrap& other)
    {
        if (this == &other) {
            data = std::make_unique<number_series>(*other.data);
        }
        return *this;
    }

    number_series_wrap::number_series_wrap(number_series_wrap&& other) noexcept
     : data(std::move(other.data)) {}

    number_series_wrap& number_series_wrap::operator=(number_series_wrap&& other) noexcept {
        if (this != &other) {
            *data = std::move(*other.data);
            std::swap(data, other.data);
        }
        return *this;
    }

    number_series_wrap::~number_series_wrap() = default;




    long int number_series_wrap::size() const
    {
        return data->size();
    }
    int number_series_wrap::get_min() const
    {
        return data->get_min();
    }
    int number_series_wrap::get_max() const
    {
        return data->get_max();
    }

    number_series_wrap number_series_wrap::make_random(int amount)
    {
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> distrib(0, 10);
        std::vector<int> temp;
        for (int i = 0; i < amount; ++i) {
            temp.push_back(distrib(gen));
        }
        return number_series_wrap{temp};
    }
    number_series_wrap& number_series_wrap::operator+=(const number_series_wrap &other)
    {
        *data+=*other.data;
        return *this;
    }
    number_series_wrap number_series_wrap::operator+(const number_series_wrap &other)
    {
        return number_series_wrap{(*data + *other.data)};
    }
    int number_series_wrap::amplitude() const
    {
        return data->amplitude();
    }
    bool number_series_wrap::operator<(const number_series_wrap &other) const
    {
        return amplitude() < other.amplitude();
    }
}  // namespace data_series
