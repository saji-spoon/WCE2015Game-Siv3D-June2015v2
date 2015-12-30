#pragma once

#include<Siv3D.hpp>

namespace shimi
{

template <class Char, typename T, size_t N> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const std::array<T, N>& con)
{
	os << L'{';

	for (auto& c : con)
	{
		os << c << L',';
	}

	return os << L'}';

}
template <class Char, typename T, size_t N>// 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, std::array<T, N>& con)
{
	Char unused;
	is >> unused;

	String str;

	for (auto& c : con)
	{
		is >> c >> unused;
	}

	return is >> unused;
}

template <class Char, typename T> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const std::vector<T>& con)
{
	os << L'{';

	os << con.size() << L',';

	for (auto& c : con)
	{
		os << c << L',';
	}

	return os << L'}';

}

template <class Char, typename T>// 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, std::vector<T>& con)
{
	con.clear();

	Char unused;
	is >> unused;
	
	size_t N;

	is >> N >> unused;

	con.resize(N);

	for (size_t i=0; i<N; ++i)
	{
		is >> con[i] >> unused;
	}

	return is >> unused;
}


template <class Char> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const std::vector<String>& con)
{
	os << con.size() << L'/';

	for (auto& c : con)
	{
		os << c << L'/';
	}

	return os;

}
template <class Char>// 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, std::vector<String>& con)
{
	con.clear();

	Char unused;

	size_t N;

	is >> N >> unused;

	con.resize(N);

	if (N == 0) return is;

	String whole = L"";

	is >> whole;

	auto strs = whole.split(L'/');

	for (size_t i = 0; i < N; ++i)
	{
		con[i] = strs[i];
	}

	return is;
}


template <class Char, typename T> // 出力ストリーム
inline std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const Optional<T>& con)
{
	if (!con)
	{
		os << L"O[N]";
	}
	else
	{
		os << L"O[" << con.value() << L']';
	}

	return os;

}
template <class Char, typename T>// 入力ストリーム
inline std::basic_istream<Char>& operator >>(std::basic_istream<Char>& is, Optional<T>& con)
{
	Char unused;

	is >> unused >> unused;

	Char buf;

	String chk = L"";

	auto pos = is.tellg();

	is >> buf;

	chk += buf;

	is >> buf;

	chk += buf;

	if (chk == L"N]")
	{
		con = none;

		return is;
	}
	else
	{
		is.seekg(pos);

		T temp;

		is >> temp >> unused;

		con = temp;

		return is;
	}
}

template <class Char>
void LogStream(std::basic_istream<Char>& is)
{
	auto pos = is.tellg();

	String str;

	LOG_DEBUG(L"===LogStream===");

	while (is >> str)
	{
		LOG_DEBUG(str);
	}

	is.seekg(pos);
}


};