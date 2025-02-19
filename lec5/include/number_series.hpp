/// Created by Marius Mikucionis <marius@cs.aau.dk>
/**
 * Definitions of number_series and number_series_wrap classes.
 */

#ifndef INCLUDE_NUMBER_SERIES_H
#define INCLUDE_NUMBER_SERIES_H

#include <vector>
#include <limits>
#include <memory>
#include <iostream>

namespace data_series
{
    class number_series
    {
        // TODO: add data field
        std::vector<int> data{};
        // TODO: add minimum and maximum fields
        int max, min;
    public:
        number_series();
        // TODO: add necessary constructors and destructors
        number_series(std::initializer_list<int>);
        number_series(std::vector<int> list);

        // TODO: add getter "size()" giving the count of numbers in the series
        long int size() const;
        // TODO: add getters for minimum and maximum
        int get_min() const;
        int get_max() const;
        // TODO: add add_value method to add numbers to the series and maintain min/max
        void add_value(int num);
        // TODO: add static member fn for factory method
        static number_series make_random(int amount);
        // TODO: add operator+= to forward calls to add_value
        number_series& operator+=(const number_series &other);
        // TODO: add operator+ which calls operator+
        number_series operator+(const number_series &other);
        // TODO: add operator< to compare amplitudes (difference between maximum and minimum)
        int amplitude() const;
        bool operator<(const number_series &other) const;
    };

    // TODO: create a light-weight wrapper class around number_series
    class number_series_wrap
    {
        // TODO: add number_series member in a smart pointer
        std::unique_ptr<number_series> data = std::make_unique<number_series>();
    public:
        number_series_wrap();
        // TODO: add the same interface as in number_series which forwards all the calls
        number_series_wrap(std::initializer_list<int> list);
        number_series_wrap(std::vector<int> list);
        number_series_wrap(number_series series);
        number_series_wrap(const number_series_wrap& other);
        number_series_wrap& operator=(const number_series_wrap& other);
        number_series_wrap(number_series_wrap&& other) noexcept;
        number_series_wrap& operator=(number_series_wrap &&other) noexcept;
        ~number_series_wrap();
        long int size() const;
        int get_min() const;
        int get_max() const;
        void add_value(int num);
        static number_series_wrap make_random(int amount);
        number_series_wrap& operator+=(const number_series_wrap &other);
        number_series_wrap operator+(const number_series_wrap &other);
        int amplitude() const;
        bool operator<(const number_series_wrap &other) const;
    };

}  // namespace data_series

#endif  // INCLUDE_NUMBER_SERIES_H
