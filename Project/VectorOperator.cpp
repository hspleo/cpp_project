
#include "VectorOperator.h"

Vect operator+(const Vect& W, const Vect& V)
{
	size_t d = W.size();
	Vect M(d);
	for (unsigned int i = 0; i<d; i++) M[i] = W[i] + V[i];
	return M;
}

Vect operator-(const Vect& W, const Vect& V)
{
	size_t d = W.size();
	Vect M(d);
	for (unsigned int i = 0; i<d; i++) M[i] = W[i] - V[i];
	return M;
}

Vect& operator /= ( Vect& W, const int& a)
{
	size_t d = W.size();
	for (unsigned int i = 0; i<d; i++) W[i] = W[i] / a;
	return W;
}

Vect operator / (const Vect& W, const int& a)
{
	size_t d = W.size();
	Vect M(d);
	for (unsigned int i = 0; i<d; i++) M[i] = W[i] / a;
	return M;
}

Vect Cumsum(const Vect& W)
{
	Vect V(W.size());
	V[0] = W[0];
	for (unsigned int i = 1; i<W.size(); i++)
		V[i] = V[i - 1] + W[i];
	return V;
}
vector<vector<vector<double>>> SetMatrix(Vect  BeatAAR, Vect  BeatCAAR, Vect  MeetAAR, Vect  MeetCAAR, Vect  MissAAR, Vect  MissCAAR)
{
	vector<vector<vector<double>>> ReturnMatrix;
	ReturnMatrix.resize(3);
	for (int i = 0; i<3; i++)
		ReturnMatrix[i].resize(2);
	ReturnMatrix[0][0] = BeatAAR ;
	ReturnMatrix[1][0] = MeetAAR ;
	ReturnMatrix[2][0] = MissAAR ;
	ReturnMatrix[0][1] = BeatCAAR ;
	ReturnMatrix[1][1] = MeetCAAR ;
	ReturnMatrix[2][1] = MissCAAR ;
	return ReturnMatrix;
};
vector<vector<string>> SetTitle()
{
	vector<vector<string>> title;
	title.resize(2);
	for (int i = 0; i<2; i++)
		title[i].resize(3);
	title[0][0] = "Beat AAR";
	title[0][1] = "Meet AAR";
	title[0][2] = "Miss AAR";
	title[1][0] = "Beat CAAR";
	title[1][1] = "Meet CAAR";
	title[1][2] = "Miss CAAR";
	return title;
};