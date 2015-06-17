#include<Siv3D.hpp>

Vec2 legToLine(const Vec2& p, const Line& l)
{
	/*
	�X���x�N�g��~v=(v1, v2)�ƒʂ�_~h=(h1, h2)���킩���Ă���ꍇ�̒���~x = (x, y)�̕�����
	-v2*x + v1*y + v2*h1 - v1*h2 = 0
	�����̕����� a*x + b*y + c = 0 �ɓ��Ă͂߂��
	�@���x�N�g��(a, b) = (-v2, v1)
	c = v2 * h1 - v1*h2 = ~h �~ ~v
	�����̕��������킩���Ă���ꍇ�̂���_����̐����̑��̋��ߕ�
	http://www.ftext.org/text/subsubsection/2365
	���Ă͂߂�ƁA���̈ꕔ�͖@���x�N�g���Ɠ_�̓��ς�A�@���x�N�g���̑傫���Œu����������
	*/
	const Vec2 v = l.vector();

	const Vec2 ab = { -v.y, v.x };//Vec(a, b)
	const double c = l.begin.cross(v);

	return p - (ab.dot(p) + c) / ab.lengthSq()*ab;
}
Vec2 legToLine2(const Vec2& p, const Line& l)
{
	//Line l�̎n�_����Vec2 p�_�ւ̃x�N�g���́A�x�N�g���Ƃ��Ă�l�ւ̎ˉe + l�̎n�_�̍��W
	return (p - l.begin).projection(l.vector()) + l.begin;
}