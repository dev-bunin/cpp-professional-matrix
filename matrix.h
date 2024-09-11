#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <ostream>
#include <cstddef>

template <typename Type, Type defaultValue>
class Matrix;

template <typename Type, Type defaultValue>
class Cell {
	using Pos = std::pair<int, int>;
	using AMatrix = Matrix<Type, defaultValue>;

public:
	Cell(Pos pos, AMatrix *parent);

	Type value() const;

	bool operator==(const Type &other) const;

	void operator=(const Type &value);

private:
	Pos m_pos;
	AMatrix *m_parent;
};

template <typename Type, Type defaultValue>
class Line {
	using Pos = std::pair<int, int>;
	using AMatrix = Matrix<Type, defaultValue>;
	using ACell = Cell<Type, defaultValue>;

public:
	Line(int id, AMatrix *parent);

	ACell operator[](int value);

private:
	int m_id;
	AMatrix *m_parent;
};

template <typename Type, Type defaultValue>
class Matrix {
	using ALine = Line<Type, defaultValue>;

	using Pos = std::pair<int, int>;
	using ValueMap = std::map<Pos, Type>;
	using Iterator = typename ValueMap::iterator;
public:
	Matrix() = default;

	Iterator find(Pos pos);
	Iterator erase(Iterator it);
	void insert(Pos pos, const Type &value);
	Iterator begin();
	Iterator end();

	ALine operator[](int value);

	size_t size() const;
private:
	ValueMap m_values;
};

/*
 * Matrix
 */

template<typename Type, Type defaultValue>
typename Matrix<Type, defaultValue>::Iterator Matrix<Type, defaultValue>::find(Pos pos)
{
	return m_values.find(pos);
}

template<typename Type, Type defaultValue>
typename Matrix<Type, defaultValue>::Iterator Matrix<Type, defaultValue>::erase(Iterator it)
{
	return m_values.erase(it);
}

template<typename Type, Type defaultValue>
void Matrix<Type, defaultValue>::insert(Pos pos, const Type &value)
{
	m_values[pos] = value;
}

template<typename Type, Type defaultValue>
typename Matrix<Type, defaultValue>::Iterator Matrix<Type, defaultValue>::begin()
{
	return m_values.begin();
}

template<typename Type, Type defaultValue>
typename Matrix<Type, defaultValue>::Iterator Matrix<Type, defaultValue>::end()
{
	return m_values.end();
}

template<typename Type, Type defaultValue>
Line<Type, defaultValue> Matrix<Type, defaultValue>::operator[](int value)
{
	return ALine(value, this);
}

template<typename Type, Type defaultValue>
size_t Matrix<Type, defaultValue>::size() const
{
	return m_values.size();
}

/*
 * Cell
 */

template<typename Type, Type defaultValue>
Cell<Type, defaultValue>::Cell(Pos pos, AMatrix *parent)
	: m_pos(pos), m_parent(parent)
{
}

template<typename Type, Type defaultValue>
Type Cell<Type, defaultValue>::value() const
{
	auto it = m_parent->find(m_pos);
	return it == m_parent->end() ? defaultValue : it->second;
}

template<typename Type, Type defaultValue>
bool Cell<Type, defaultValue>::operator==(const Type &other) const
{
	return other == value();
}

template<typename Type, Type defaultValue>
void Cell<Type, defaultValue>::operator=(const Type &value)
{
	auto it = m_parent->find(m_pos);
	if (value == defaultValue) {
		// Задают дефолтное значение
		if (it == m_parent->end()) {
			// Значение и так отсутствует ничего делать не надо
			return;
		}
		// Очищаем старое значение
		m_parent->erase(it);
		return;
	}
	// Задают нормальное значение
	if (it != m_parent->end()) {
		// содержит значение в этой ячейке. Просто перезаписываем
		it->second = value;
		return;
	}

	// Ячейка пустая. Нужно создать
	m_parent->insert(m_pos, value);
}

/*
 * Line
 */

template<typename Type, Type defaultValue>
Line<Type, defaultValue>::Line(int id, AMatrix *parent)
	: m_id(id), m_parent(parent)
{
}

template<typename Type, Type defaultValue>
Cell<Type, defaultValue> Line<Type, defaultValue>::operator[](int value)
{
	return ACell({m_id, value}, m_parent);
}

#endif // MATRIX_H
