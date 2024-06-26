#define CATCH_CONFIG_MAIN

#include <iostream>
#include <cstring>
#include "catch.hpp"

#if __has_include("Vector.hpp")
# define FILE_EXIST true
# include "Vector.hpp"
#else
# define FILE_EXIST false
#endif

#define GENERATE_HAS_MEMBER_FUNCTION(functionName, memberFunction) \
  template <typename T, typename RESULT, typename... ARGS>         \
  class has_##functionName {                                       \
	typedef std::true_type yes;                                    \
	typedef std::false_type no;                                    \
	template <typename U, RESULT (U::*)(ARGS...)>                  \
	struct Check;                                                  \
	template <typename U>                                          \
	static yes func(Check<U, &U::memberFunction> *);               \
	template <typename>                                            \
	static no func(...);                                           \
																   \
   public:                                                         \
	typedef has_##functionName type;                               \
	static constexpr bool value =                                  \
		std::is_same<decltype(func<T>(0)), yes>::value;            \
  };
#define GENERATE_HAS_CONST_MEMBER_FUNCTION(functionName, memberFunction) \
  template <typename T, typename RESULT, typename... ARGS>               \
  class has_const_##functionName {                                       \
	typedef std::true_type yes;                                          \
	typedef std::false_type no;                                          \
	template <typename U, RESULT (U::*)(ARGS...) const>                  \
	struct Check;                                                        \
	template <typename U>                                                \
	static yes func(Check<U, &U::memberFunction> *);                     \
	template <typename>                                                  \
	static no func(...);                                                 \
																		 \
   public:                                                               \
	typedef has_const_##functionName type;                               \
	static constexpr bool value =                                        \
		std::is_same<decltype(func<T>(0)), yes>::value;                  \
  };


#define GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(name) \
	GENERATE_HAS_MEMBER_FUNCTION(name, name)
#define GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(name) \
	GENERATE_HAS_CONST_MEMBER_FUNCTION(name, name)

template <class T, class Enable = void>
struct isDefined
{
	static constexpr bool value = false;
};

template <class T>
struct isDefined<T, std::enable_if_t<(sizeof(T) > 0)>>
{
	static constexpr bool value = true;
};

template <typename T>
class Vector;

struct TestStruct
{
	int Data;
};

GENERATE_HAS_MEMBER_FUNCTION(assignment_operator, operator=)
GENERATE_HAS_MEMBER_FUNCTION(move_assignment_operator, operator=)

GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(size)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(capacity)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(empty)

GENERATE_HAS_CONST_MEMBER_FUNCTION(at_operator, operator[])
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(at)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(front)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(back)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(data)

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(clear)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(insert)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(erase)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(push_back)
GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(pop_back)

#define WARN_CHECK(condition, code)							\
	if constexpr (condition) {			\
		INFO("PASS: " #code " is defined");						\
	} else {												\
		WARN("WARNING: " #code " is not defined");				\
	}

#define FUNCTION_EXIST(name, code)	\
	WARN_CHECK(vector_function_ ##name##_is_defined, code)				\
	THEN(#name " defintion exist:\n" #code) {	\
		REQUIRE(vector_function_ ##name##_is_defined);					\
	}
#define OPERATOR_EXIST(name, look, code)	\
	WARN_CHECK(vector_ ##name##_operator_is_defined, code)				\
	THEN(#look " operator defintion exist:\n" #code) {	\
		REQUIRE(vector_ ##name##_operator_is_defined);					\
	}
#define DEFINE_PRINT(cond, code) \
	std::cout << (cond ? "[OK]  " : "[ ]  ") << #code << std::endl




TEMPLATE_TEST_CASE_SIG("Check if all necessary files, class definitions, and function definitions exist for this assignment.\nIf they do, they are tested.\n", "",
	((int Dummy, typename T_vector_class, typename T_vector_int, typename T_test_struct),
	Dummy, T_vector_class, T_vector_int, T_test_struct),
	(42, Vector<TestStruct>, Vector<int>, TestStruct)) {

	static constexpr bool header_file_vector_hpp_exist = FILE_EXIST;

	GIVEN("The student has been instructed to create a headerfile for the assignment.") {
		THEN("A file 'vector.hpp' exist in the directory 'include/'") {
			REQUIRE(header_file_vector_hpp_exist);
		}
	}

	GIVEN("The requested headerfile exist.") {
		if constexpr (!header_file_vector_hpp_exist) {
			WARN("This section is unlocked when the headefile exist.");
		} else {

			static constexpr bool vector_class_is_defined = isDefined<T_vector_class>::value;

			GIVEN("The student has been instructed to create a templated class 'Vector' for the assignment.") {
				THEN("A templated class 'Vector' should be defined") {
					REQUIRE(vector_class_is_defined);	
				}
			}

			if constexpr (!vector_class_is_defined) {
				WARN("This section is unlocked when the class is defined.");
			} else {

				static constexpr bool vector_constructor_is_defined = std::is_constructible<T_vector_class>::value;
				static constexpr bool vector_copy_constructor_is_defined = std::is_constructible<T_vector_class, const T_vector_class&>::value;
				static constexpr bool vector_copy_move_constructor_is_defined = std::is_constructible<T_vector_class, T_vector_class&&>::value;
				static constexpr bool vector_assignment_operator_is_defined = has_assignment_operator<T_vector_class, T_vector_class&, const T_vector_class&>::value;
				static constexpr bool vector_assignment_move_operator_is_defined = has_move_assignment_operator<T_vector_class, T_vector_class&, T_vector_class&&>::value;

				static constexpr bool vector_const_function_size_is_defined = has_const_size<T_vector_class, int>::value;
				static constexpr bool vector_const_function_capacity_is_defined = has_const_capacity<T_vector_class, int>::value;
				static constexpr bool vector_const_function_empty_is_defined = has_const_empty<T_vector_class, bool>::value;

				static constexpr bool vector_const_at_operator_is_defined = has_const_at_operator<T_vector_class, TestStruct&, int>::value;
				static constexpr bool vector_const_function_at_is_defined = has_const_at<T_vector_class, TestStruct&, int>::value;
				static constexpr bool vector_const_function_front_is_defined = has_const_front<T_vector_class, TestStruct&>::value;
				static constexpr bool vector_const_function_back_is_defined = has_const_back<T_vector_class, TestStruct&>::value;
				static constexpr bool vector_const_function_data_is_defined = has_const_data<T_vector_class, const TestStruct*>::value;

				static constexpr bool vector_function_clear_is_defined = has_clear<T_vector_class, void>::value;
				static constexpr bool vector_function_insert_is_defined = has_insert<T_vector_class, void, int, const TestStruct&>::value;
				static constexpr bool vector_function_erase_is_defined = has_erase<T_vector_class, void, int>::value;
				static constexpr bool vector_function_push_back_is_defined = has_push_back<T_vector_class, void, const TestStruct&>::value;
				static constexpr bool vector_function_pop_back_is_defined = has_pop_back<T_vector_class, void>::value;

				static constexpr bool all_is_defined = vector_class_is_defined
					&& vector_constructor_is_defined
					&& vector_copy_constructor_is_defined
					&& vector_copy_move_constructor_is_defined
					&& vector_assignment_operator_is_defined
					&& vector_assignment_move_operator_is_defined
					&& vector_const_function_size_is_defined
					&& vector_const_function_capacity_is_defined
					&& vector_const_function_empty_is_defined
					&& vector_const_at_operator_is_defined
					&& vector_const_function_at_is_defined
					&& vector_const_function_front_is_defined
					&& vector_const_function_back_is_defined
					&& vector_const_function_data_is_defined
					&& vector_function_clear_is_defined
					&& vector_function_insert_is_defined
					&& vector_function_erase_is_defined
					&& vector_function_push_back_is_defined
					&& vector_function_pop_back_is_defined;

				
				THEN("List of functions to declare:") {
					std::cout << "\n\n----- List of functions to declare -----\n\n";
					DEFINE_PRINT(vector_constructor_is_defined, Vector<T>::Vector());
					DEFINE_PRINT(vector_copy_constructor_is_defined, Vector<T>::Vector(const Vector<T>&));
					DEFINE_PRINT(vector_copy_move_constructor_is_defined, Vector<T>::Vector(Vector<T>&&));
					DEFINE_PRINT(vector_assignment_operator_is_defined, Vector<T>& Vector<T>::operator=(const Vector<T>&));
					DEFINE_PRINT(vector_assignment_move_operator_is_defined, Vector<TestStruct>& Vector<T>::operator=(Vector<T>&&));

					DEFINE_PRINT(vector_const_function_size_is_defined, int Vector<T>::size());
					DEFINE_PRINT(vector_const_function_capacity_is_defined, int Vector<T>::capacity());
					DEFINE_PRINT(vector_const_function_empty_is_defined, bool Vector<T>::empty());

					DEFINE_PRINT(vector_const_at_operator_is_defined, T& Vector<T>::operator[](int));
					DEFINE_PRINT(vector_const_function_at_is_defined, T& Vector<T>::at(int));
					DEFINE_PRINT(vector_const_function_front_is_defined, T& Vector<T>::front());
					DEFINE_PRINT(vector_const_function_back_is_defined, T& Vector<T>::back());
					DEFINE_PRINT(vector_const_function_data_is_defined, const T* Vector<T>::data());

					DEFINE_PRINT(vector_function_clear_is_defined, void Vector<T>::clear());
					DEFINE_PRINT(vector_function_insert_is_defined, void Vector<T>::insert(int, const T&));
					DEFINE_PRINT(vector_function_erase_is_defined, void Vector<T>::erase(int));
					DEFINE_PRINT(vector_function_push_back_is_defined, void Vector<T>::push_back(const T&));
					DEFINE_PRINT(vector_function_pop_back_is_defined, void Vector<T>::pop_back());
					std::cout << "\nNote: The list above do not reveal if a function should be const or not.\n";
					std::cout << "      The list only reveal the datatype of each parameter, not the name.\n";
				}

				THEN("Constructor definition exist:\nVector<T>::Vector()") {
					REQUIRE(vector_constructor_is_defined);
				}

				THEN("Copy constructor definition exist:\nVector<T>::Vector(const Vector<T>&)") {
					REQUIRE(vector_copy_constructor_is_defined);
				}

				THEN("Copy move constructor definition exist:\nVector<T>::Vector(Vector<T>&&)") {
					REQUIRE(vector_copy_move_constructor_is_defined);
				}

				THEN("Copy operator definition exist:\nVector<T>& Vector<T>::operator=(const Vector<T>&)") {
					REQUIRE(vector_assignment_operator_is_defined);
				}

				THEN("Copy move operator definition exist:\nVector<T>& Vector<T>::operator=(Vector<T>&&)") {				
					REQUIRE(vector_assignment_move_operator_is_defined);
				}



				THEN("Function definition exist:\nint Vector<T>::size()") {
					INFO("Hint: If the test don't find your function, remember that some functions are expected to be const. Making a return value a const type do not make the function const.");
					REQUIRE(vector_const_function_size_is_defined);
				}

				THEN("Function definition exist:\nint Vector<T>::capacity()") {
					INFO("Hint: If the test don't find your function, remember that some functions are expected to be const. Making a return value a const type do not make the function const.");
					REQUIRE(vector_const_function_capacity_is_defined);
				}

				THEN("Function definition exist:\nbool Vector<T>::empty()") {
					INFO("Hint: If the test don't find your function, remember that some functions are expected to be const. Making a return value a const type do not make the function const.");
					REQUIRE(vector_const_function_empty_is_defined);
				}



				THEN("Operator definition exist:\nT& Vector<T>::operator[](int)") {
					REQUIRE(vector_const_at_operator_is_defined);
				}

				THEN("Function definition exist:\nT& Vector<T>::at(int)") {
					INFO("Hint: If the test don't find your function, remember that some functions are expected to be const. Making a return value a const type do not make the function const.");
					REQUIRE(vector_const_function_at_is_defined);
				}

				THEN("Function definition exist:\nT& Vector<T>::front()") {
					INFO("Hint: If the test don't find your function, remember that some functions are expected to be const. Making a return value a const type do not make the function const.");
					REQUIRE(vector_const_function_front_is_defined);
				}

				THEN("Function definition exist:\nT& Vector<T>::back()") {
					INFO("Hint: If the test don't find your function, remember that some functions are expected to be const. Making a return value a const type do not make the function const.");
					REQUIRE(vector_const_function_back_is_defined);
				}

				THEN("Function definition exist:\nconst T* Vector<T>::data()") {
					REQUIRE(vector_const_function_data_is_defined);
				}



				THEN("Function definition exist:\nvoid Vector<T>::clear()") {
					REQUIRE(vector_function_clear_is_defined);
				}

				THEN("Function definition exist:\nvoid Vector<T>::insert(int, const T&)") {
					REQUIRE(vector_function_insert_is_defined);
				}

				THEN("Function definition exist:\nvoid Vector<T>::erase(int)") {
					REQUIRE(vector_function_erase_is_defined);
				}

				THEN("Function definition exist:\nvoid Vector<T>::push_back(const T&)") {
					REQUIRE(vector_function_push_back_is_defined);
				}

				THEN("Function definition exist:\nvoid Vector<T>::pop_back()") {
					REQUIRE(vector_function_pop_back_is_defined);
				}
				

				GIVEN("All functions should be defined.") {
					if constexpr (!all_is_defined) {
						WARN("This section is unlocked when all functions are defined.");
					} else {
						WHEN("An empty vector for int is created.") {
							T_vector_int vec;

							THEN("The Vector should be initialized with some default values.") {
								REQUIRE(vec.size() == 0);
								REQUIRE(vec.capacity() >= 0);
							}

							THEN("empty() should return true.") {
								REQUIRE(vec.empty());
							}

							GIVEN("Functions for accessing references throw exceptions as there are no elements to return references to.") {
								bool throw_at = false;
								bool throw_at_operator = false;
								bool throw_front = false;
								bool throw_back = false;

								THEN("at(0) should throw exeption.") {
									try {
										vec.at(0);
									} catch (...) {
										throw_at = true;
									}
									INFO("Accessing at(0) on an empty vector, expecting to catch an exception.");
									REQUIRE(throw_at);
								}

								THEN("[0] should throw exeption.") {
									try {
										vec[0];
									} catch (...) {
										throw_at_operator = true;
									}
									INFO("Accessing [0] on an empty vector, expecting to catch an exception.");
									REQUIRE(throw_at_operator);
								}

								THEN("front() should throw exeption.") {
									try {
										vec.front();
									} catch (...) {
										throw_front = true;
									}
									INFO("Accessing front() on an empty vector, expecting to catch an exception.");
									REQUIRE(throw_front);
								}

								THEN("back() should throw exeption.") {
									try {
										vec.back();
									} catch (...) {
										throw_back = true;
									}
									INFO("Accessing back() on an empty vector, expecting to catch an exception.");
									REQUIRE(throw_back);
								}
							}

							GIVEN("Removing elements from an empty vector should not be possible.") {
								THEN("pop_back() should return without changing the vector, without throwing an exception.") {
									
									bool throw_pop_back_on_empty_vector = false;
									int original_capacity = vec.capacity();
									const int* original_array_start = vec.data();

									try {
										vec.pop_back();
									} catch (...) {
										throw_pop_back_on_empty_vector = true;
									}

									INFO("Called pop_back() on an empty vector");
									REQUIRE(vec.size() == 0);
									REQUIRE(vec.data() == original_array_start);
									REQUIRE(vec.capacity() == original_capacity);
									REQUIRE(!throw_pop_back_on_empty_vector);
								}
							}

							WHEN("100 elements are added to the vector using push_back. Values start at 1000, and is increased by one for each element.") {

								static constexpr int start_number = 1000;
								static constexpr int end_number = start_number + 100;

								for (int i = start_number; i < end_number; i++) {
									vec.push_back(i);
								}



								THEN("The copy constructor should be able to create a copy of the vector") {

									int original_size = vec.size();
									int original_capacity = vec.capacity();
									const int* original_array_start = vec.data();

									T_vector_int copy(vec);
									INFO("A copy was created using the copy constructor.");

									THEN("The original vector should not be changed.") {
										REQUIRE(vec.data() == original_array_start);
										REQUIRE(vec.capacity() == original_capacity);
										REQUIRE(vec.size() == original_size);
									}

									THEN("The copy should have the same properties as the original.") {
										REQUIRE(copy.capacity() == original_capacity);
										REQUIRE(copy.size() == original_size);
									}

									THEN("The copy should contain a copy (a new array containing the same values) of the array in the original.") {
										REQUIRE(copy.data() != vec.data());
										REQUIRE(copy.size() == vec.size());
										
										for (int i = 0; i < copy.size(); i++) {
											INFO("Index i was " + std::to_string(i));
											REQUIRE(copy[i] == original_array_start[i]); 
										}
									}
								}

								GIVEN("A copy can be created using the copy operator=.") {
									int original_size = vec.size();
									int original_capacity = vec.capacity();
									const int* original_array_start = vec.data();

									WHEN("A new copy is created using the copy operator=.") {

										T_vector_int copy;
										copy = vec;

										THEN("The original vector should not be changed.") {
											REQUIRE(vec.data() == original_array_start);
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.size() == original_size);
										}

										THEN("The copy should have the same properties as the original.") {
											REQUIRE(copy.capacity() == original_capacity);
											REQUIRE(copy.size() == original_size);
										}

										THEN("The copy should contain a copy (a new array containing the same values) of the array in the original.") {
											REQUIRE(copy.data() != vec.data());
											REQUIRE(copy.size() == vec.size());
											
											for (int i = 0; i < copy.size(); i++) {
												INFO("Index i was " + std::to_string(i));
												REQUIRE(copy[i] == original_array_start[i]); 
											}
										}
									}

									WHEN("The vector is assigned to copy itself") {
										vec = vec;

										THEN("The vector should not be changed.") {
											REQUIRE(vec.data() == original_array_start);
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.size() == original_size);

											for (int i = 0; i < original_size; i++) {
												INFO("Index i was " + std::to_string(i));
												REQUIRE(vec[i] == original_array_start[i]); 
											}
										}
									}
								}

								GIVEN("The move constructor should be able to take ownership of the content from another vector.") {
									int original_size = vec.size();
									int original_capacity = vec.capacity();
									const int* original_array_start = vec.data();

									WHEN("A new vector is created using the move constructor with the original vector.") {
										T_vector_int moved(std::move(vec));
		
										THEN("The new vector should contain same properties the original vector had.") {
											REQUIRE(moved.capacity() == original_capacity);
											REQUIRE(moved.size() == original_size);
										}

										THEN("The new vector should take the ownership over the internal array.") {
											REQUIRE(moved.data() == original_array_start);
										}

										THEN("The original vector should be left in a safe state.") {
											INFO("The original vector should not have ownership of the original array anymore.");
											INFO("The original vector should be empty.");
											REQUIRE(vec.data() != original_array_start);
											REQUIRE(vec.size() == 0);

											if (vec.data() == nullptr) {
												INFO("If the original vectors array is set to null, its capacity should be 0.")
												REQUIRE(vec.capacity() == 0);
											}
										}

										THEN("It should be possible to add elements to the now empty original vector.") {
											int size_to_trigger_expand = static_cast<int>(original_capacity*1.1);

											INFO("push_back(0)");
											vec.push_back(0);

											REQUIRE(vec.size() == 1);
											REQUIRE(vec.capacity() > 0);

											for (int i = 1; i < size_to_trigger_expand; i++) {
												vec.push_back(i);
											}
										}

										THEN("It should be possible to add elements to new vector.") {

											int size_to_trigger_expand = static_cast<int>(original_capacity*1.1);

											INFO("push_back(" + std::to_string(original_size) + ")");
											moved.push_back(original_size);

											REQUIRE(moved.size() == original_size+1);
											REQUIRE(moved.capacity() > 0);

											for (int i = original_size+1; i < size_to_trigger_expand; i++) {
												moved.push_back(i);
												INFO("push_back(" + std::to_string(i) + ")");
												REQUIRE(moved.back() == i);
											}
										}
									}
								}

								GIVEN("The move operator should be able to take ownership of the content from another vector.") {
									int original_size = vec.size();
									int original_capacity = vec.capacity();
									const int* original_array_start = vec.data();

									WHEN("A new vector is created. The move operator is used with the original vector.") {
										T_vector_int moved;
										moved = std::move(vec);

										THEN("The new vector should contain same properties the original vector had.") {
											REQUIRE(moved.capacity() == original_capacity);
											REQUIRE(moved.size() == original_size);
										}

										THEN("The new vector should take the ownership over the internal array.") {
											REQUIRE(moved.data() == original_array_start);
										}

										THEN("The original vector should be left in a safe state.") {
											INFO("The original vector should not have ownership of the original array anymore.");
											INFO("The original vector should be empty.");
											REQUIRE(vec.data() != original_array_start);
											REQUIRE(vec.size() == 0);

											if (vec.data() == nullptr) {
												INFO("If the original vectors array is set to null, its capacity should be 0.")
												REQUIRE(vec.capacity() == 0);
											}
										}

										THEN("It should be possible to add elements to the now empty original vector.") {
											int size_to_trigger_expand = static_cast<int>(original_capacity*1.1);

											INFO("push_back(0)");
											vec.push_back(0);

											REQUIRE(vec.size() == 1);
											REQUIRE(vec.capacity() > 0);

											for (int i = 1; i < size_to_trigger_expand; i++) {
												vec.push_back(i);
											}
										}

										THEN("It should be possible to add elements to new vector.") {

											int size_to_trigger_expand = static_cast<int>(original_capacity*1.1);

											INFO("push_back(" + std::to_string(original_size) + ")");
											moved.push_back(original_size);

											REQUIRE(moved.size() == original_size+1);
											REQUIRE(moved.capacity() > 0);

											for (int i = original_size+1; i < size_to_trigger_expand; i++) {
												moved.push_back(i);
												INFO("push_back(" + std::to_string(i) + ")");
												REQUIRE(moved.back() == i);
											}
										}
									}

									WHEN("The vector uses the move operator on itself.") {
										vec = std::move(vec);

										THEN("The vector should contain same properties as before.") {
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.size() == original_size);
										}

										THEN("The vector should still have ownership over the same internal array.") {
											REQUIRE(vec.data() == original_array_start);
										}

										THEN("It should still be possible to add elements to vector.") {

											int size_to_trigger_expand = static_cast<int>(original_capacity*1.1);
											for (int i = original_size; i < size_to_trigger_expand; i++) {
												vec.push_back(i);
												INFO("push_back(" + std::to_string(i) + ")");
												REQUIRE(vec.back() == i);
											}
										}
									}
								}



								GIVEN("[] operator should be able to access elements.") {

									THEN("Elements of valid indicies is possible to access.") {
										for (int i = 0; i < 100; i++) {
											INFO("When index (i) was " + std::to_string(i));
											REQUIRE(vec[i] == (start_number + i));
										}
									}

									THEN("An invalid index should result with a thrown exception.") {
										bool throw_at_negative_index = false;
										bool throw_at_size_index = false;
										bool throw_at_a_to_large_index = false;

										try {
											vec[-1];
										} catch (...) {
											throw_at_negative_index = true;
										}
										INFO("Accessing with index [-1], expecting to catch an exception.");
										REQUIRE(throw_at_negative_index);

										int size = vec.size();
										try {
											vec[size];
										} catch (...) {
											throw_at_size_index = true;
										}
										INFO("Accessing with index [" + std::to_string(size) + "] (same as size), expecting to catch an exception.");
										REQUIRE(throw_at_size_index);

										try {
											vec[202398474];
										} catch (...) {
											throw_at_a_to_large_index = true;
										}
										INFO("Accessing with index [202398474], expecting to catch an exception.");
										REQUIRE(throw_at_a_to_large_index);
									}
								}

								GIVEN("at() should be able to access elements.") {

									THEN("Elements of valid indicies is possible to access.") {
										for (int i = 0; i < 100; i++) {
											INFO("When index (i) was " + std::to_string(i));
											REQUIRE(vec.at(i) == (start_number + i));
										}
									}

									THEN("An invalid index should result with a thrown exception.") {
										bool throw_at_negative_index = false;
										bool throw_at_size_index = false;
										bool throw_at_a_to_large_index = false;

										try {
											vec.at(-1);
										} catch (...) {
											throw_at_negative_index = true;
										}
										INFO("Accessing with index (-1), expecting to catch an exception.");
										REQUIRE(throw_at_negative_index);

										int size = vec.size();
										try {
											vec.at(size);
										} catch (...) {
											throw_at_size_index = true;
										}
										INFO("Accessing with index (" + std::to_string(size) + "), same as size, expecting to catch an exception.");
										REQUIRE(throw_at_size_index);

										try {
											vec.at(202398474);
										} catch (...) {
											throw_at_a_to_large_index = true;
										}
										INFO("Accessing with index (202398474), expecting to catch an exception.");
										REQUIRE(throw_at_a_to_large_index);
									}
								}

								THEN("front() should return the first number.") {
									REQUIRE(vec.front() == start_number);
								}

								THEN("back() should return the last number.") {
									REQUIRE(vec.back() == end_number-1);
								}

								THEN("data() should return a pointer to the start of the array.") {
									const int* internal_array = vec.data();

									for (int i = 0; i < 100; i++) {
										INFO("When index (i) was " + std::to_string(i));
										REQUIRE(internal_array[i] == (start_number + i));
									}
								}



								THEN("size() should return 100.") {
									REQUIRE(vec.size() == 100);
								}

								THEN("capacity() should be at least 100.") {
									REQUIRE(vec.capacity() >= 100);

									WHEN("More elements are added to the vector until the number of elements reaches the capacity, forcing it to expand.") {
										int original_size = vec.size();
										int original_capacity = vec.capacity();
										const int* original_array_start = vec.data();

										int last_capacity = original_capacity;

										float smallest_expand_factor = -1.0f;
										bool has_expanded = false;

										int size_to_trigger_expand = static_cast<int>(original_capacity*100);
										for (int i = original_size; i <= size_to_trigger_expand; i++) {
											vec.push_back(i);

											if (vec.capacity() != last_capacity) { // Has expanded
												float new_factor = ((float)vec.capacity() / (float)last_capacity);
												if (new_factor < smallest_expand_factor || smallest_expand_factor < 0.0f) { // Find smallest expand factor
													smallest_expand_factor = new_factor;
												}
												last_capacity = vec.capacity();
												has_expanded = true;
											}
										}

										INFO("Smallest detected expansion factor was " + std::to_string(smallest_expand_factor));

										THEN("The internal array should bee replaced by a new and larger dynamic array, containing the same elements as the original.") {
											REQUIRE(has_expanded);
											REQUIRE(vec.capacity() > original_capacity);
											REQUIRE(vec.data() != original_array_start);
										}

										THEN("The vector should expand a reasonable factor.") {
											INFO("This test checks if the size of the vector expanded with a smallest factor of at least 1.4");
											INFO("Note that the capacity should expand with a factor, and not a constant number.");
											REQUIRE(has_expanded);
											REQUIRE(smallest_expand_factor >= 1.4f);
										}
									}
								}

								THEN("empty() should return false.") {
									REQUIRE(!vec.empty());
								}



								WHEN("clear() is called to clear all the elements from the vector.") {
									int original_capacity = vec.capacity();
									vec.clear();

									THEN("The vector should become empty") {
										REQUIRE(vec.size() == 0);
										REQUIRE(vec.empty());
									}

									WHEN("Three new elements are added to the vector.") {
										int size_to_trigger_expand = static_cast<int>(original_capacity*1.1);
										for (int i = 0; i < size_to_trigger_expand; i++) {
											vec.push_back(i);
											INFO("push_back(" + std::to_string(i) + ")");
											REQUIRE(vec.back() == i);
										}
									}
								}

								GIVEN("insert() can be used to insert an element in the vector.") {

									static constexpr int insert_index = 10;
									static constexpr int inserted_element = 5555;

									int original_size = vec.size();
									std::unique_ptr<int[]> original_array_copy(new int[vec.size()]);
									memcpy(original_array_copy.get(), vec.data(), vec.size()*sizeof(int));

									WHEN("Using insert() with a valid index (0 <= index <= size)") {
										INFO("The number " + std::to_string(inserted_element) + " was inserted at index " + std::to_string(insert_index) + ".")
										vec.insert(insert_index, inserted_element);

										THEN("The size should increase by one.") {
											REQUIRE(vec.size() == original_size+1);
										}

										THEN("The elements before the inserted index should not be changed.") {
											for (int i = 0; i < insert_index; i++) {
												INFO("Index i was " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i]);
											}
										}

										THEN("The inserted index should contain the new element.") {
											REQUIRE(vec[insert_index] == inserted_element);
										}
										
										THEN("The elements after the inserted index should not be changed.") {
											for (int i = insert_index+1; i < vec.size(); i++) {
												INFO("Index i was " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i-1]);
											}
										}
									}

									WHEN("Using insert() with a valid index (0 <= index <= size)") {
										WHEN("An object is inserted at the first index (index = 0)") {
											INFO("The number " + std::to_string(inserted_element) + " was inserted at index 0.")
											vec.insert(0, inserted_element);

											THEN("The size should increase by one.") {
												REQUIRE(vec.size() == original_size+1);
											}

											THEN("The inserted index should contain the new element.") {
												REQUIRE(vec[0] == inserted_element);
											}
										}

										WHEN("An object is inserted at the back (index = size())") {
											int last_index = vec.size();
											INFO("The number " + std::to_string(inserted_element) + " was inserted at index " + std::to_string(last_index) + ".")
											vec.insert(last_index, inserted_element);

											THEN("The size should increase by one.") {
												REQUIRE(vec.size() == original_size+1);
											}

											THEN("The inserted index should contain the new element.") {
												REQUIRE(vec[last_index] == inserted_element);
											}
										}
									}

									GIVEN("Using insert() with an invalid index, the function should return without changing the state of the vector, and no exception should be thrown.") {
										
										int original_capacity = vec.capacity();
										const int* original_array_start = vec.data();
										
										WHEN("An element is inserted at index -1.") {
											
											bool throw_insert_negative_index = false;							
											INFO("The current size is " + std::to_string(original_size));
											INFO("An element is inserted at index " + std::to_string(-1));
											try {
												vec.insert(-1, 12345);
											} catch (...) {
												throw_insert_negative_index = true;
											}

											REQUIRE(vec.size() == original_size);
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.data() == original_array_start);
											REQUIRE(!throw_insert_negative_index);

											for (int i = 0; i < original_size; i++) {
												INFO("Comparing to copy of original array at index " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i]);
											}
										}

										WHEN("An element is inserted at an index larger than the size of the vector.") {
											
											bool throw_insert_index_larger_than_size = false;							
											INFO("The current size is " + std::to_string(original_size));
											INFO("An element is inserted at index " + std::to_string(original_size + 5));
											try {
												vec.insert(original_size + 5, 12345);
											} catch (...) {
												throw_insert_index_larger_than_size = true;
											}

											REQUIRE(vec.size() == original_size);
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.data() == original_array_start);
											REQUIRE(!throw_insert_index_larger_than_size);

											for (int i = 0; i < original_size; i++) {
												INFO("Comparing to copy of original array at index " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i]);
											}
										}
									}
								}

								GIVEN("erase() can be used to erase one element from the vector.") {

									WHEN("erase() is used with a valid index, the element at that index is erased and all the following elements should be moved to fill the now empty spot in order to not leave any 'gaps'") {
										static constexpr int erased_index = 10;

										int original_size = vec.size();
										std::unique_ptr<int[]> original_array_copy(new int[vec.size()]);
										memcpy(original_array_copy.get(), vec.data(), vec.size()*sizeof(int));

										INFO("The element at index " + std::to_string(erased_index) + " was erased.");
										vec.erase(erased_index);

										THEN("The size should decrease by one.") {
											REQUIRE(vec.size() == original_size-1);
										}

										THEN("The elements before the erased index should not be changed.") {
											for (int i = 0; i < erased_index; i++) {
												INFO("Index i was " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i]);
											}
										}
										
										THEN("The the rest of the elements, starting after the erased index, should be 'moved' one step to the left in the array to fill the gap.") {
											for (int i = erased_index; i < vec.size(); i++) {
												INFO("Index i was " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i+1]);
											}
										}
									}

									GIVEN("erase() is used with an invalid index, the function should return without changing the state of the vector, and no exception should be thrown.") {
										
										
										int original_size = vec.size();
										int original_capacity = vec.capacity();
										const int* original_array_start = vec.data();
										std::unique_ptr<int[]> original_array_copy(new int[original_size]);

										memcpy(original_array_copy.get(), original_array_start, original_size*sizeof(int));
										
										WHEN("An element is 'erased' at index -1.") {
											
											bool throw_erase_negative_index = false;							
											INFO("The current size is " + std::to_string(original_size));
											INFO("An element is 'erased' at index " + std::to_string(-1));
											try {
												vec.erase(-1);
											} catch (...) {
												throw_erase_negative_index = true;
											}

											REQUIRE(vec.size() == original_size);
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.data() == original_array_start);
											REQUIRE(!throw_erase_negative_index);

											for (int i = 0; i < original_size; i++) {
												INFO("Comparing to copy of original array at index " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i]);
											}
										}

										WHEN("An element is 'erased' at an index larger than the size of the vector.") {
											
											bool throw_erase_index_larger_than_size = false;							
											INFO("The current size is " + std::to_string(original_size));
											INFO("An element is 'erased' at index " + std::to_string(original_size + 5));
											try {
												vec.erase(original_size + 5);
											} catch (...) {
												throw_erase_index_larger_than_size = true;
											}

											REQUIRE(vec.size() == original_size);
											REQUIRE(vec.capacity() == original_capacity);
											REQUIRE(vec.data() == original_array_start);
											REQUIRE(!throw_erase_index_larger_than_size);

											for (int i = 0; i < original_size; i++) {
												INFO("Comparing to copy of original array at index " + std::to_string(i));
												REQUIRE(vec[i] == original_array_copy[i]);
											}
										}
									}
								}

								WHEN("pop_back() is used to erase the last element in the vector") {
									int original_size = vec.size();
									int original_back = vec.back();
									int expected_back_after_pop = vec[vec.size()-2];

									INFO("The last element " + std::to_string(original_back) + " is popped.");
									vec.pop_back();

									THEN("The size of the vector should decrease by one.") {
										REQUIRE(vec.size() == original_size-1);
									}

									THEN("The previous next to last element " + std::to_string(expected_back_after_pop) + " should now be the new last element.") {
										REQUIRE(vec.back() == expected_back_after_pop);
									}
								}
							}
						}
					}
				}	
			}
		}
	}
}


struct LargeType {
private:
	static constexpr int SIZE = 128;
	int data[SIZE];
public:
	int value;
	LargeType(int nr = 0) : value(nr) {
		for (int i = 0; i < SIZE; i++) {
			data[i] = 0;
		}
	}
	LargeType(const LargeType& other) : value(other.value) {
		for (int i = 0; i < SIZE; i++) {
			data[i] = 0;
		}
	}
	LargeType(LargeType&& other) : value(other.value) {
		for (int i = 0; i < SIZE; i++) {
			data[i] = 0;
		}
	}
	void operator=(const LargeType& other) {
		value = other.value; // If memorycheck mention this line, it's possibly some loop accessing outside of allocated memory. Check possible indicies.
	}
	void operator=(LargeType&& other) {
		value = other.value; // If memorycheck mention this line, it's possibly some loop accessing outside of allocated memory. Check possible indicies.
	}
	bool operator==(const LargeType& other) {
		return value == other.value;
	}
	bool operator!=(const LargeType& other) {
		return value != other.value;
	}
};

TEMPLATE_TEST_CASE_SIG("Extra tests using a larger datatype to detect read/write outside of allocated memory.\n", "",
	((int Dummy, typename T_vector_LargeType),
	Dummy, T_vector_LargeType),
	(42, Vector<LargeType>)) {

	int size_before_expansion = 0;
	{
		T_vector_LargeType to_be_expanded;
		
		INFO("Pushing 10 objects at back to force capacity to be not zero");
		for (int i = 0; i < 10; i++) {
			to_be_expanded.push_back(LargeType());
		}

		int capacity_before_expansion = to_be_expanded.capacity();
		do {
			size_before_expansion = to_be_expanded.size();
			to_be_expanded.push_back(LargeType());
		} while (to_be_expanded.capacity() == capacity_before_expansion);
	}

	GIVEN("insert() should be able to add an object at the first and last index.") {
		GIVEN("An empty vector") {
			T_vector_LargeType vec;

			WHEN("Inserting 100 objects at index '0'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: 0, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(0, LargeType(i));
				}

				THEN("The vector should contain 100 objects") {
					REQUIRE(vec.size() == 100);
				}

				THEN("Then objects should have the correct values") {
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].value == (99-i));
					}
				}
			}

			WHEN("Inserting 100 objects at the last index 'size'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: " + std::to_string(vec.size()) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size(), LargeType(i));
				}

				THEN("The vector should contain 100 objects") {
					REQUIRE(vec.size() == 100);
				}

				THEN("Then objects should have the correct values") {
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].value == i);
					}
				}
			}
		}
	}

	GIVEN("Copy-constructor should not cause memory leaks") {
		GIVEN("An empty vector 'a'") {
			T_vector_LargeType a;
			WHEN("Vector 'b' is created as a copy of 'a'") {
				T_vector_LargeType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("An empty vector 'a'") {
			T_vector_LargeType a;

			INFO("Pushing 100 objects at back of 'a', then calling clear()")
			for (int i = 0; i < 100; i++) {
				a.push_back(LargeType(i));
			}
			a.clear();

			WHEN("Vector 'b' is created as a copy of 'a'") {
				T_vector_LargeType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("A vector 'a' containing 50 objects") {
			T_vector_LargeType a;

			INFO("Pushing 50 objects at back of 'a'")
			for (int i = 0; i < 50; i++) {
				a.push_back(LargeType(i));
			}

			WHEN("Vector 'b' is created by copying 'a'") {
				int size_of_a = a.size();
				T_vector_LargeType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].value == i);
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("Vector 'a' is added objects until next push_back() causes expansion of capacity") {
			T_vector_LargeType a;
			
			for (int i = 0; i < size_before_expansion; i++) {
				a.push_back(LargeType(i));
			}

			WHEN("Vector 'b' is created by copying 'a'") {
				int size_of_a = a.size();
				T_vector_LargeType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].value == i);
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
	}

	GIVEN("Move-constructor should not cause memory leaks") {
		GIVEN("An empty vector 'a'") {
			T_vector_LargeType a;
			WHEN("Vector 'b' is created by moving 'a'") {
				T_vector_LargeType b(std::move(a));

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("An empty vector 'a'") {
			T_vector_LargeType a;

			INFO("Pushing 100 objects at back of 'a', then calling clear()")
			for (int i = 0; i < 100; i++) {
				a.push_back(LargeType(i));
			}
			a.clear();

			WHEN("Vector 'b' is created by moving 'a'") {
				T_vector_LargeType b(std::move(a));

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("A vector 'a' containing 50 objects") {
			T_vector_LargeType a;

			INFO("Pushing 50 objects at back of 'a'")
			for (int i = 0; i < 50; i++) {
				a.push_back(LargeType(i));
			}

			WHEN("Vector 'b' is created by moving 'a'") {
				int size_of_a = a.size();
				T_vector_LargeType b(std::move(a));

				THEN("Properties of 'b' should be correct") {			
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].value == i);
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("Vector 'a' is added objects until next push_back() causes expansion of capacity") {
			T_vector_LargeType a;
			
			for (int i = 0; i < size_before_expansion; i++) {
				a.push_back(LargeType(i));
			}

			WHEN("Vector 'b' is created by moving 'a'") {
				int size_of_a = a.size();
				T_vector_LargeType b(std::move(a));

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].value == i);
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(LargeType(i));
					}
					b.clear();
				}
			}
		}
	}

	GIVEN("copy-assignment should not cause memory leaks if the vector 'a'lready has elements") {
		GIVEN("Vector 'a' has 10 objects") {
			T_vector_LargeType a;
			for (int i = 0; i < 10; i++) {
				a.push_back(LargeType(i));
			}

			GIVEN("Vector 'b' has 5 objects") {
				T_vector_LargeType b;
				for (int i = 0; i < 5; i++) {
					b.push_back(LargeType(i));
				}

				WHEN("'a' is copied to 'b'") {
					b = a;
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].value == i);
							REQUIRE(b[i].value == a[i].value);
						}

						WHEN("'b' is copied back to 'a'") {
							a = b;
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].value == i);
									REQUIRE(a[i].value == b[i].value);
								}
							}
						}
					}
				}
			}

			GIVEN("Vector 'b' has 150 objects") {
				T_vector_LargeType b;
				for (int i = 0; i < 150; i++) {
					b.push_back(LargeType(i));
				}

				WHEN("'a' is copied to 'b'") {
					b = a;
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].value == i);
							REQUIRE(b[i].value == a[i].value);
						}

						WHEN("'b' is copied back to 'a'") {
							a = b;
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].value == i);
									REQUIRE(a[i].value == b[i].value);
								}
							}
						}
					}
				}
			}
			GIVEN("Vector 'b' is 'filled' (push_back will trigger a higher capacity") {
				T_vector_LargeType b;
				for (int i = 0; i < size_before_expansion; i++) {
					b.push_back(LargeType(i));
				}

				WHEN("'a' is copied to 'b'") {
					b = a;
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].value == i);
							REQUIRE(b[i].value == a[i].value);
						}

						WHEN("'b' is copied back to 'a'") {
							a = b;
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].value == i);
									REQUIRE(a[i].value == b[i].value);
								}
							}
						}
					}
				}
			}
		}
	}

	GIVEN("move-assignment should not cause memory leaks if the vector 'a'lready has elements") {
		GIVEN("Vector 'a' has 10 objects") {
			T_vector_LargeType a;
			for (int i = 0; i < 10; i++) {
				a.push_back(LargeType(i));
			}

			GIVEN("Vector 'b' has 5 objects") {
				T_vector_LargeType b;
				for (int i = 0; i < 5; i++) {
					b.push_back(LargeType(i));
				}

				WHEN("'a' is moved to 'b'") {
					b = std::move(a);
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].value == i);
						}

						WHEN("'b' is moved back to 'a'") {
							a = std::move(b);
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].value == i);
								}
							}
						}
					}
				}
			}

			GIVEN("Vector 'b' has 150 objects") {
				T_vector_LargeType b;
				for (int i = 0; i < 150; i++) {
					b.push_back(LargeType(i));
				}

				WHEN("'a' is moved to 'b'") {
					b = std::move(a);
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].value == i);
						}

						WHEN("'b' is moved back to 'a'") {
							a = std::move(b);
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].value == i);
								}
							}
						}
					}
				}
			}

			GIVEN("Vector 'b' is 'filled' (push_back will trigger a higher capacity") {
				T_vector_LargeType b;
				for (int i = 0; i < size_before_expansion; i++) {
					b.push_back(LargeType(i));
				}

				WHEN("'a' is moved to 'b'") {
					b = std::move(a);
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].value == i);
						}

						WHEN("'b' is moved back to 'a'") {
							a = std::move(b);
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].value == i);
								}
							}
						}
					}
				}
			}
		}
	}

	GIVEN("erase() should be able to remove at valid indices") {
		GIVEN("A vector of 10 objects") {
			T_vector_LargeType vec;
			for (int i = 0; i < 10; i++) {
				vec.push_back(LargeType(i));
			}

			WHEN("erase() is used to remove the first object 10 times") {
				for (int i = 0; i < 10; i++) {
					vec.erase(0);
				}
				THEN("The vector should be empty") {
					REQUIRE(vec.empty());
					REQUIRE(vec.size() == 0);
				}
			}

			WHEN("erase() is used to remove the last object (at index 'size-1') 10 times") {
				for (int i = 0; i < 10; i++) {
					vec.erase(vec.size()-1);
				}
				THEN("The vector should be empty") {
					REQUIRE(vec.empty());
					REQUIRE(vec.size() == 0);
				}
			}
		}
	}

	GIVEN("erase() should not cause memory leaks") {
		GIVEN("An empty vector") {
			T_vector_LargeType vec;
			WHEN("100 elements are added, 100 are erased, 100 are added again, 100 are erased again... 10 times") {
				
				WHEN("..by erasing the first element") {
					for (int t = 0; t < 10; t++) {
						for (int i = 0; i < 100; i++) {
							vec.push_back(i);
						}
						for (int i = 0; i < 100; i++) {
							vec.erase(0);
						}
					}

					THEN("The vector should be empty") {
						REQUIRE(vec.size() == 0);
						REQUIRE(vec.empty());
					}

					WHEN("Pushing 50 more elements at back") {
						for (int i = 0; i < 50; i++) {
							vec.push_back(i);
						}

						THEN("Properties should be correct") {
							REQUIRE(vec.size() == 50);
							for (int i = 0; i < 50; i++) {
								REQUIRE(vec.at(i).value == i);
							}
						}
					}
				}

				WHEN("..by erasing the last element (at index 'size-1')") {
					for (int t = 0; t < 10; t++) {
						for (int i = 0; i < 100; i++) {
							vec.push_back(i);
						}
						for (int i = 0; i < 100; i++) {
							vec.erase(vec.size()-1);
						}
					}

					THEN("The vector should be empty") {
						REQUIRE(vec.size() == 0);
						REQUIRE(vec.empty());
					}

					WHEN("Pushing 50 more elements at back") {
						for (int i = 0; i < 50; i++) {
							vec.push_back(i);
						}

						THEN("Properties should be correct") {
							REQUIRE(vec.size() == 50);
							for (int i = 0; i < 50; i++) {
								REQUIRE(vec.at(i).value == i);
							}
						}
					}
				}
			}
		}
		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_LargeType vec;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(LargeType(i));
			}

			THEN("erase() on first index until empty should not cause memory leaks") {
				while(!vec.empty()) {
					vec.erase(0);
				}
				REQUIRE(vec.empty());
			}

			THEN("erase() on last index (at index 'size-1') until empty should not cause memory leaks") {
				while(!vec.empty()) {
					vec.erase(vec.size()-1);
				}
				REQUIRE(vec.empty());
			}
		}
	}

	GIVEN("insert() should be possible after clear()") {
		GIVEN("A vector of 10 objects is cleared") {
			T_vector_LargeType vec;

			for (int i = 0; i < 10; i++) {
				vec.push_back(LargeType(i));
			}

			vec.clear();

			THEN("The vector should be empty") {
				REQUIRE(vec.size() == 0);
				REQUIRE(vec.empty());
			}

			WHEN("Inserting 100 new objects at index '0'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: 0, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(0, LargeType(i));
				}
				THEN("Properties should be correct") {
					REQUIRE(vec.size() == 100);
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].value == (99-i));
					}
				}
			}

			WHEN("Inserting 100 new objects at index 'size'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: " + std::to_string(vec.size()) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size(), LargeType(i));
				}
				THEN("Properties should be correct") {
					REQUIRE(vec.size() == 100);
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].value == i);
					}
				}
			}
		}
	}

	GIVEN("insert() should handle incorrect index without throwing an exception or modify the vector") {
		GIVEN("A newly created (empty) vector") {
			T_vector_LargeType vec;

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using clear())") {
			T_vector_LargeType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			vec.clear();

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using pop_back())") {
			T_vector_LargeType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.pop_back();
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using erase(0))") {
			T_vector_LargeType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.erase(0);
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A vector with 10 elements") {
			T_vector_LargeType vec;

			int expected_size = 0;
			for (int i = 0; i < 10; i++) {
				vec.push_back(LargeType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_LargeType vec;

			int expected_size = 0;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(LargeType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, LargeType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}
	}

	GIVEN("erase() should handle incorrect index without throwing an exception or modify the vector") {
		GIVEN("A newly created (empty) vector") {
			T_vector_LargeType vec;

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using clear())") {
			T_vector_LargeType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			vec.clear();

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using pop_back())") {
			T_vector_LargeType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.pop_back();
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using erase(0))") {
			T_vector_LargeType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.erase(0);
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A vector with 10 elements") {
			T_vector_LargeType vec;

			int expected_size = 0;
			for (int i = 0; i < 10; i++) {
				vec.push_back(LargeType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_LargeType vec;

			int expected_size = 0;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(LargeType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(LargeType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}
	}

	GIVEN("clear() should not cause memory leaks") {
		WHEN("Pushing 100 objects  at back, clearing, pushing 100 objects again, clearing again... 10 times") {
			T_vector_LargeType vec;

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 100; j++) {
					vec.push_back(LargeType(j));
				}
				vec.clear();
			}

			THEN("The vector should be empty") {
				REQUIRE(vec.size() == 0);
				REQUIRE(vec.empty());
			}

			WHEN("Pushing 50 new objects at back to the now cleared vector") {
				for (int i = 0; i < 50; i++) {
					vec.push_back(LargeType(i));
				}

				THEN("The vector should have the correct proterties") {
					REQUIRE(vec.size() == 50);
					for (int i = 0; i < 50; i++) {
						REQUIRE(vec[i].value == i);
					}
				}
			}
		}

		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_LargeType vec;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(LargeType(i));
			}

			THEN("clear() should not cause memory leaks") {
				vec.clear();
				REQUIRE(vec.empty());
			}
		}
	}

	GIVEN("pop_back() should not cause memory leaks") {
		WHEN("Pushing 100 objects at back, popping all, pushing 100 objects again, popping all again... 10 times") {
			T_vector_LargeType vec;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 100; j++) {
					vec.push_back(LargeType(j));
				}
				for (int j = 0; j < 100; j++) {
					vec.pop_back();
				}
			}

			THEN("The vector should be empty") {
				REQUIRE(vec.size() == 0);
				REQUIRE(vec.empty());
			}

			WHEN("Pushing 50 new objects at back to the now cleared vector") {
				for (int i = 0; i < 50; i++) {
					vec.push_back(LargeType(i));
				}

				THEN("The vector should have the correct proterties") {
					REQUIRE(vec.size() == 50);
					for (int i = 0; i < 50; i++) {
						REQUIRE(vec[i].value == i);
					}
				}
			}
		}
		GIVEN("A 'full' vector (push_back will trigger a higher capacity") {
			T_vector_LargeType vec;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(LargeType(i));
			}

			THEN("pop_back() until vector is empty should not cause memory leaks") {
				while (!vec.empty()) {
					vec.pop_back();
				}
				REQUIRE(vec.empty());
			}
		}
	}

	GIVEN("pop_back() on empty vector should not decrease size") {
		GIVEN("A newly created vector") {
			T_vector_LargeType vec;
			WHEN("pop_back() is used") {
				vec.pop_back();
				THEN("size is still 0") {
					REQUIRE(vec.size() == 0);
				}
			}
		}

		GIVEN("A used vector that is now empty") {
			T_vector_LargeType vec;
			for (int i = 0; i < 10; i++) {
				vec.push_back(LargeType(i));
			}
			WHEN("Empty by using clear()") {
				vec.clear();

				WHEN("pop_back() is used") {
					vec.pop_back();
					THEN("size is still 0") {
						REQUIRE(vec.size() == 0);
					}
				}
			}
			WHEN("Empty by using pop_back()") {
				while(!vec.empty()) {
					vec.pop_back();
				}

				WHEN("pop_back() is used") {
					vec.pop_back();
					THEN("size is still 0") {
						REQUIRE(vec.size() == 0);
					}
				}
			}
		}
	}
}
















struct DynamicType {
private:
	int* data;
public:
	DynamicType(int nr = 0) : data(new int(nr)) {}
	DynamicType(const DynamicType& other) : data(new int(other.get_data())) {}
	DynamicType(DynamicType&& other) : data(other.data) {
		other.data = nullptr;
	}
	~DynamicType() {
		delete data;
	}
	int get_data() const {
		return (data) ? *data : -1;
	}
	void operator=(const DynamicType& other) {
		if (data && other.data) {
			*data = *other.data;
		} else if (data) { // only other.data is nullptr
			delete data;
			data = nullptr;
		} else { // only data is nullptr
			data = new int(other.get_data());
		}
	}
	void operator=(DynamicType&& other) {
		delete data;
		data = other.data;
		other.data = nullptr;
	}
	bool operator==(const DynamicType& other) {
		return get_data() == other.get_data();
	}
	bool operator!=(const DynamicType& other) {
		return get_data() != other.get_data();
	}
};


TEMPLATE_TEST_CASE_SIG("Extra tests using a datatype that allocate dynamic memory internally to detect if objects are copied correctly by the vector.\n", "",
	((int Dummy, typename T_vector_DynamicType),
	Dummy, T_vector_DynamicType),
	(42, Vector<DynamicType>)) {

	int size_before_expansion = 0;
	{
		T_vector_DynamicType to_be_expanded;
		
		INFO("Pushing 10 objects at back to force capacity to be not zero");
		for (int i = 0; i < 10; i++) {
			to_be_expanded.push_back(DynamicType());
		}

		int capacity_before_expansion = to_be_expanded.capacity();
		do {
			size_before_expansion = to_be_expanded.size();
			to_be_expanded.push_back(DynamicType());
		} while (to_be_expanded.capacity() == capacity_before_expansion);
	}

	GIVEN("insert() should be able to add an object at the first and last index.") {
		GIVEN("An empty vector") {
			T_vector_DynamicType vec;

			WHEN("Inserting 100 objects at index '0'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: 0, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(0, DynamicType(i));
				}

				THEN("The vector should contain 100 objects") {
					REQUIRE(vec.size() == 100);
				}

				THEN("Then objects should have the correct values") {
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].get_data() == (99-i));
					}
				}
			}

			WHEN("Inserting 100 objects at index 'size'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: " + std::to_string(vec.size()) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size(), DynamicType(i));
				}

				THEN("The vector should contain 100 objects") {
					REQUIRE(vec.size() == 100);
				}

				THEN("Then objects should have the correct values") {
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].get_data() == i);
					}
				}
			}
		}
	}

	GIVEN("Copy-constructor should not cause memory leaks") {
		GIVEN("An empty vector 'a'") {
			T_vector_DynamicType a;
			WHEN("Vector 'b' is created as a copy of 'a'") {
				T_vector_DynamicType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("An empty vector 'a'") {
			T_vector_DynamicType a;

			INFO("100 objects are added to a and is then cleared using clear()")
			for (int i = 0; i < 100; i++) {
				a.push_back(DynamicType(i));
			}
			a.clear();

			WHEN("Vector 'b' is created as a copy of 'a'") {
				T_vector_DynamicType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("A vector 'a' containing 50 objects") {
			T_vector_DynamicType a;

			INFO("50 objects are added to 'a'")
			for (int i = 0; i < 50; i++) {
				a.push_back(DynamicType(i));
			}

			WHEN("Vector 'b' is created by copying 'a'") {
				int size_of_a = a.size();
				T_vector_DynamicType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].get_data() == (i));
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("Vector 'a' is added objects until next push_back() causes expansion of capacity") {
			T_vector_DynamicType a;
			
			for (int i = 0; i < size_before_expansion; i++) {
				a.push_back(DynamicType(i));
			}

			WHEN("Vector 'b' is created by copying 'a'") {
				int size_of_a = a.size();
				T_vector_DynamicType b(a);

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].get_data() == (i));
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
	}

	GIVEN("Move-constructor should not cause memory leaks") {
		GIVEN("An empty vector 'a'") {
			T_vector_DynamicType a;
			WHEN("Vector 'b' is created by moving 'a'") {
				T_vector_DynamicType b(std::move(a));

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("An empty vector 'a'") {
			T_vector_DynamicType a;

			INFO("100 objects are added to a and is then cleared using clear()")
			for (int i = 0; i < 100; i++) {
				a.push_back(DynamicType(i));
			}
			a.clear();

			WHEN("Vector 'b' is created by moving 'a'") {
				T_vector_DynamicType b(std::move(a));

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == 0);
					REQUIRE(b.empty());
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("A vector 'a' containing 50 objects") {
			T_vector_DynamicType a;

			INFO("50 objects are added to 'a'")
			for (int i = 0; i < 50; i++) {
				a.push_back(DynamicType(i));
			}

			WHEN("Vector 'b' is created by moving 'a'") {
				int size_of_a = a.size();
				T_vector_DynamicType b(std::move(a));

				THEN("Properties of 'b' should be correct") {			
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].get_data() == (i));
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
		GIVEN("Vector 'a' is added objects until next push_back() causes expansion of capacity") {
			T_vector_DynamicType a;
			
			for (int i = 0; i < size_before_expansion; i++) {
				a.push_back(DynamicType(i));
			}

			WHEN("Vector 'b' is created by moving 'a'") {
				int size_of_a = a.size();
				T_vector_DynamicType b(std::move(a));

				THEN("Properties of 'b' should be correct") {
					REQUIRE(b.size() == size_of_a);
					for (int i = 0; i < size_of_a; i++) {
						REQUIRE(b[i].get_data() == (i));
					}
				}

				THEN("'b' should be able to be used as normal") {
					for (int i = 0; i < 10; i++) {
						b.push_back(DynamicType(i));
					}
					b.clear();
				}
			}
		}
	}

	GIVEN("copy-assignment should not cause memory leaks if the vector 'a'lready has elements") {
		GIVEN("Vector 'a' has 10 objects") {
			T_vector_DynamicType a;
			for (int i = 0; i < 10; i++) {
				a.push_back(DynamicType(i));
			}

			GIVEN("Vector 'b' has 5 objects") {
				T_vector_DynamicType b;
				for (int i = 0; i < 5; i++) {
					b.push_back(DynamicType(i));
				}

				WHEN("'a' is copied to 'b'") {
					b = a;
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].get_data() == (i));
							REQUIRE(b[i].get_data() == a[i].get_data());
						}

						WHEN("'b' is copied back to 'a'") {
							a = b;
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].get_data() == (i));
									REQUIRE(a[i].get_data() == b[i].get_data());
								}
							}
						}
					}
				}
			}

			GIVEN("Vector 'b' has 150 objects") {
				T_vector_DynamicType b;
				for (int i = 0; i < 150; i++) {
					b.push_back(DynamicType(i));
				}

				WHEN("'a' is copied to 'b'") {
					b = a;
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].get_data() == (i));
							REQUIRE(b[i].get_data() == a[i].get_data());
						}

						WHEN("'b' is copied back to 'a'") {
							a = b;
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].get_data() == (i));
									REQUIRE(a[i].get_data() == b[i].get_data());
								}
							}
						}
					}
				}
			}
			GIVEN("Vector 'b' is 'filled' (push_back will trigger a higher capacity)") {
				T_vector_DynamicType b;
				for (int i = 0; i < size_before_expansion; i++) {
					b.push_back(DynamicType(i));
				}

				WHEN("'a' is copied to 'b'") {
					b = a;
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].get_data() == (i));
							REQUIRE(b[i].get_data() == a[i].get_data());
						}

						WHEN("'b' is copied back to 'a'") {
							a = b;
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].get_data() == (i));
									REQUIRE(a[i].get_data() == b[i].get_data());
								}
							}
						}
					}
				}
			}
		}
	}

	GIVEN("move-assignment should not cause memory leaks if the vector 'a'lready has elements") {
		GIVEN("Vector 'a' has 10 objects") {
			T_vector_DynamicType a;
			for (int i = 0; i < 10; i++) {
				a.push_back(DynamicType(i));
			}

			GIVEN("Vector 'b' has 5 objects") {
				T_vector_DynamicType b;
				for (int i = 0; i < 5; i++) {
					b.push_back(DynamicType(i));
				}

				WHEN("'a' is moved to 'b'") {
					b = std::move(a);
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].get_data() == (i));
						}

						WHEN("'b' is moved back to 'a'") {
							a = std::move(b);
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].get_data() == (i));
								}
							}
						}
					}
				}
			}

			GIVEN("Vector 'b' has 150 objects") {
				T_vector_DynamicType b;
				for (int i = 0; i < 150; i++) {
					b.push_back(DynamicType(i));
				}

				WHEN("'a' is moved to 'b'") {
					b = std::move(a);
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].get_data() == (i));
						}

						WHEN("'b' is moved back to 'a'") {
							a = std::move(b);
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].get_data() == (i));
								}
							}
						}
					}
				}
			}

			GIVEN("Vector 'b' is 'filled' (push_back will trigger a higher capacity)") {
				T_vector_DynamicType b;
				for (int i = 0; i < size_before_expansion; i++) {
					b.push_back(DynamicType(i));
				}

				WHEN("'a' is moved to 'b'") {
					b = std::move(a);
					THEN("'b' should contain a's elements, and no memory leaks should be detected") {
						for (int i = 0; i < 10; i++) {
							REQUIRE(b[i].get_data() == (i));
						}

						WHEN("'b' is moved back to 'a'") {
							a = std::move(b);
							THEN("'a' should contain 'b's elements, and no memory leaks should be detected") {
								for (int i = 0; i < 10; i++) {
									REQUIRE(a[i].get_data() == (i));
								}
							}
						}
					}
				}
			}
		}
	}

	GIVEN("erase() should be able to remove at valid indices") {
		GIVEN("A vector of 10 objects") {
			T_vector_DynamicType vec;
			for (int i = 0; i < 10; i++) {
				vec.push_back(DynamicType(i));
			}

			WHEN("erase() is used to remove the first object 10 times") {
				for (int i = 0; i < 10; i++) {
					vec.erase(0);
				}
				THEN("The vector should be empty") {
					REQUIRE(vec.empty());
					REQUIRE(vec.size() == 0);
				}
			}

			WHEN("erase() is used to remove the last object (at index 'size-1') 10 times") {
				for (int i = 0; i < 10; i++) {
					vec.erase(vec.size()-1);
				}
				THEN("The vector should be empty") {
					REQUIRE(vec.empty());
					REQUIRE(vec.size() == 0);
				}
			}
		}
	}

	GIVEN("erase() should not cause memory leaks") {
		GIVEN("An empty vector") {
			T_vector_DynamicType vec;
			WHEN("100 elements are added, 100 are erased, 100 are added again, 100 are erased again... 10 times") {
				
				WHEN("..by erasing the first element") {
					for (int t = 0; t < 10; t++) {
						for (int i = 0; i < 100; i++) {
							vec.push_back(i);
						}
						for (int i = 0; i < 100; i++) {
							vec.erase(0);
						}
					}

					THEN("The vector should be empty") {
						REQUIRE(vec.size() == 0);
						REQUIRE(vec.empty());
					}

					WHEN("Pushing 50 more elements at back") {
						for (int i = 0; i < 50; i++) {
							vec.push_back(i);
						}

						THEN("Properties should be correct") {
							REQUIRE(vec.size() == 50);
							for (int i = 0; i < 50; i++) {
								REQUIRE(vec.at(i).get_data() == (i));
							}
						}
					}
				}

				WHEN("..by erasing the last element (at index 'size-1')") {
					for (int t = 0; t < 10; t++) {
						for (int i = 0; i < 100; i++) {
							vec.push_back(i);
						}
						for (int i = 0; i < 100; i++) {
							vec.erase(vec.size()-1);
						}
					}

					THEN("The vector should be empty") {
						REQUIRE(vec.size() == 0);
						REQUIRE(vec.empty());
					}

					WHEN("Pushing 50 more elements at back") {
						for (int i = 0; i < 50; i++) {
							vec.push_back(i);
						}

						THEN("Properties should be correct") {
							REQUIRE(vec.size() == 50);
							for (int i = 0; i < 50; i++) {
								REQUIRE(vec.at(i).get_data() == (i));
							}
						}
					}
				}
			}
		}
		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_DynamicType vec;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(DynamicType(i));
			}

			THEN("erase() on first index until empty should not cause memory leaks") {
				while(!vec.empty()) {
					vec.erase(0);
				}
				REQUIRE(vec.empty());
			}

			THEN("erase() on last index (at index 'size-1') until empty should not cause memory leaks") {
				while(!vec.empty()) {
					vec.erase(vec.size()-1);
				}
				REQUIRE(vec.empty());
			}
		}
	}

	GIVEN("insert() should be possible after clear()") {
		GIVEN("A vector of 10 objects is cleared") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 10; i++) {
				vec.push_back(DynamicType(i));
			}

			vec.clear();

			THEN("The vector should be empty") {
				REQUIRE(vec.size() == 0);
				REQUIRE(vec.empty());
			}

			WHEN("Inserting 100 new objects at index '0'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: 0, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(0, DynamicType(i));
				}
				THEN("Properties should be correct") {
					REQUIRE(vec.size() == 100);
					for (int i = 99; i >= 0; i--) {
						REQUIRE(vec[i].get_data() == (99-i));
					}
				}
			}

			WHEN("Inserting 100 new objects at index 'size-1'") {
				for (int i = 0; i < 100; i++) {
					INFO("index: " + std::to_string(vec.size()) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size(), DynamicType(i));
				}
				THEN("Properties should be correct") {
					REQUIRE(vec.size() == 100);
					for (int i = 0; i < 100; i++) {
						REQUIRE(vec[i].get_data() == (i));
					}
				}
			}
		}
	}

	GIVEN("insert() should handle incorrect index without throwing an exception or modify the vector") {
		GIVEN("A newly created (empty) vector") {
			T_vector_DynamicType vec;

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using clear())") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			vec.clear();

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using pop_back())") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.pop_back();
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using erase(0))") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.erase(0);
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A vector with 10 elements") {
			T_vector_DynamicType vec;

			int expected_size = 0;
			for (int i = 0; i < 10; i++) {
				vec.push_back(DynamicType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_DynamicType vec;

			int expected_size = 0;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(DynamicType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("inserting at index -1") {
				try {
					INFO("index: -1, size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(-1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("inserting at index 'size+1'") {
				try {
					INFO("index: " + std::to_string(vec.size()+1) + ", size: " + std::to_string(vec.size()) + ", capacity: " + std::to_string(vec.capacity()));
					vec.insert(vec.size()+1, DynamicType());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}
	}

	GIVEN("erase() should handle incorrect index without throwing an exception or modify the vector") {
		GIVEN("A newly created (empty) vector") {
			T_vector_DynamicType vec;

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using clear())") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			vec.clear();

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using pop_back())") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.pop_back();
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A used empty vector (20 objects added and cleared using erase(0))") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 20; i++) {
				vec.push_back(20);
			}
			for (int i = 0; i < 20; i++) {
				vec.erase(0);
			}

			int expected_size = 0;
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A vector with 10 elements") {
			T_vector_DynamicType vec;

			int expected_size = 0;
			for (int i = 0; i < 10; i++) {
				vec.push_back(DynamicType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}

		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_DynamicType vec;

			int expected_size = 0;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(DynamicType(++expected_size));
			}
			REQUIRE(vec.size() == expected_size);

			bool exception_was_thrown = false;

			WHEN("erasing at index -1") {
				try {
					vec.erase(-1);
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}

			WHEN("erasing at index 'size'") {
				try {
					vec.erase(vec.size());
				} catch (...) {
					exception_was_thrown = true;
				}
				THEN("An exception should not be thrown") {
					REQUIRE(!exception_was_thrown);
				}
				THEN("The size should not change") {
					REQUIRE(vec.size() == expected_size);
				}

				THEN("The vector will still be usable") {
					INFO("Pushing 50 more objects at back, checking size for each push")
					for (int i = 0; i < 50; i++) {
						vec.push_back(DynamicType(++expected_size));
						REQUIRE(vec.size() == expected_size);
					}
				}
			}
		}
	}

	GIVEN("clear() should not cause memory leaks") {
		WHEN("Pushing 100 objects at back, clearing, pushing 100 objects again, clearing again... 10 times") {
			T_vector_DynamicType vec;

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 100; j++) {
					vec.push_back(DynamicType(j));
				}
				vec.clear();
			}

			THEN("The vector should be empty") {
				REQUIRE(vec.size() == 0);
				REQUIRE(vec.empty());
			}

			WHEN("Pushing 50 new objects at back to the now cleared vector") {
				for (int i = 0; i < 50; i++) {
					vec.push_back(DynamicType(i));
				}

				THEN("The vector should have the correct proterties") {
					REQUIRE(vec.size() == 50);
					for (int i = 0; i < 50; i++) {
						REQUIRE(vec[i].get_data() == (i));
					}
				}
			}
		}

		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_DynamicType vec;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(DynamicType(i));
			}

			THEN("clear() should not cause memory leaks") {
				vec.clear();
				REQUIRE(vec.empty());
			}
		}
	}

	GIVEN("pop_back() should not cause memory leaks") {
		WHEN("Pushing 100 objects at back, popping all, pushing 100 objects again, popping all again... 10 times") {
			T_vector_DynamicType vec;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 100; j++) {
					vec.push_back(DynamicType(j));
				}
				for (int j = 0; j < 100; j++) {
					vec.pop_back();
				}
			}

			THEN("The vector should be empty") {
				REQUIRE(vec.size() == 0);
				REQUIRE(vec.empty());
			}

			WHEN("Pushing 50 new objects at back to the now cleared vector") {
				for (int i = 0; i < 50; i++) {
					vec.push_back(DynamicType(i));
				}

				THEN("The vector should have the correct proterties") {
					REQUIRE(vec.size() == 50);
					for (int i = 0; i < 50; i++) {
						REQUIRE(vec[i].get_data() == (i));
					}
				}
			}
		}
		GIVEN("A 'full' vector (push_back will trigger a higher capacity)") {
			T_vector_DynamicType vec;
			for (int i = 0; i < size_before_expansion; i++) {
				vec.push_back(DynamicType(i));
			}

			THEN("pop_back() until vector is empty should not cause memory leaks") {
				while (!vec.empty()) {
					vec.pop_back();
				}
				REQUIRE(vec.empty());
			}
		}
	}

	GIVEN("pop_back() on empty vector should not decrease size") {
		GIVEN("A newly created vector") {
			T_vector_DynamicType vec;
			WHEN("pop_back() is used") {
				vec.pop_back();
				THEN("size is still 0") {
					REQUIRE(vec.size() == 0);
				}
			}
		}

		GIVEN("A used vector that is now empty") {
			T_vector_DynamicType vec;
			for (int i = 0; i < 10; i++) {
				vec.push_back(DynamicType(i));
			}
			WHEN("Empty by using clear()") {
				vec.clear();

				WHEN("pop_back() is used") {
					vec.pop_back();
					THEN("size is still 0") {
						REQUIRE(vec.size() == 0);
					}
				}
			}
			WHEN("Empty by using pop_back()") {
				while(!vec.empty()) {
					vec.pop_back();
				}

				WHEN("pop_back() is used") {
					vec.pop_back();
					THEN("size is still 0") {
						REQUIRE(vec.size() == 0);
					}
				}
			}
		}
	}
}