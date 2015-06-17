#include<Siv3D.hpp>

Vec2 legToLine(const Vec2& p, const Line& l)
{
	/*
	傾きベクトル~v=(v1, v2)と通る点~h=(h1, h2)がわかっている場合の直線~x = (x, y)の方程式
	-v2*x + v1*y + v2*h1 - v1*h2 = 0
	直線の方程式 a*x + b*y + c = 0 に当てはめると
	法線ベクトル(a, b) = (-v2, v1)
	c = v2 * h1 - v1*h2 = ~h × ~v
	直線の方程式がわかっている場合のある点からの垂線の足の求め方
	http://www.ftext.org/text/subsubsection/2365
	当てはめると、式の一部は法線ベクトルと点の内積や、法線ベクトルの大きさで置き換えられる
	*/
	const Vec2 v = l.vector();

	const Vec2 ab = { -v.y, v.x };//Vec(a, b)
	const double c = l.begin.cross(v);

	return p - (ab.dot(p) + c) / ab.lengthSq()*ab;
}
Vec2 legToLine2(const Vec2& p, const Line& l)
{
	//Line lの始点からVec2 p点へのベクトルの、ベクトルとしてのlへの射影 + lの始点の座標
	return (p - l.begin).projection(l.vector()) + l.begin;
}