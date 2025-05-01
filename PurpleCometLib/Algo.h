#include <algorithm>
#pragma once 
namespace Algo {

	template <typename T>
	bool contains(const T& vec, const T& sub) {
		return std::search(vec.begin(), vec.end(), sub.begin(), sub.end()) != vec.end();

	}
	template <typename Container, typename T>
	bool contains(const Container& c, const T& value) {
		return std::find(c.begin(), c.end(), value) != c.end();
	}

	template <typename T>
	T remove_duplicates(const T& container) {
		T result = container;
		auto last = std::unique(result.begin(), result.end());
		result.erase(last, result.end());
		return result;
	}
	template <typename Container>
	typename Container::value_type mean(const Container& container) {
		using ValueType = typename Container::value_type;

		if (container.empty()) {
			throw std::invalid_argument("Cannot calculate the mean of an empty container.");
		}

		ValueType sum = std::accumulate(container.begin(), container.end(), ValueType{});
		return sum / static_cast<typename std::common_type<ValueType, int>::type>(container.size());
	}
	template <typename Container>
		int argmax(const Container& data) {
		return std::distance(data.begin(), std::max_element(data.begin(), data.end()));
	}

	template <typename Container>
	int argmin(const Container& data) {
		return std::distance(data.begin(), std::min_element(data.begin(), data.end()));
	}
	
	template <typename Container>
	typename Container::value_type sum(const Container& container) {
		using ValueType = typename Container::value_type;
		return std::accumulate(container.begin(), container.end(), ValueType(0));
	}
	
	template <typename T>
	T try_until_equal(std::function<T(int)> generator,std::function<bool(const T&)> condition,int max_attempts = 1000)
	{
	for (int i = 0; i < max_attempts; ++i) {
		T value = generator(i);
		if (condition(value)) {
			return value;
		}
	}
	throw std::runtime_error("Condition not met within max attempts.");
	}
	
		template<typename Container, typename T>
		bool anySatisfies(const Container& container, std::function<bool(T)> property) {
			for (const auto& element : container) {
				if (property(element)) {
					return true;  // Return true if any element satisfies the property
				}
			}
			return false;  // Return false if no element satisfies the property
		}
double Prod(std::function<float(float)> func, int start, int end){
double result = 1.0;
	for (int i = start; i <= end; i++) {
		result *= func(i);
	}
	return result;
	}

	double Sum(std::function<float(float)> func, int start, int end){
	double result =0.0;
		for (int i = start; i <= end; i++) {
			result += func(i);
		}
		return result;
		} 
};
