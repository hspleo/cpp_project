#include"Display.h"
#include"Stock.h"
#include"VectorOperator.h"
#include "Colors.h"
using namespace std;
void Menu(const Group& Beat, const Group& Meet, const Group& Miss, const vector<vector<vector<double>>>& ResultMatrix)
{
	string c = "0";

CheckPoint:
	{

		cout << greencolor << " --------------------------------------------------------------------" << endl;
		cout << " |Make sure to use capital letters for the stock selection and      |" << endl;
		cout << " |enter a number when asked for a number                            |" << endl;
		cout << " --------------------------------------------------------------------" << endl << defcolor;
		cout << " *                                                                  *" << endl;
		cout << " --------------------------------------------------------------------" << endl;
		cout << " |Would you like to...                                              |" << endl;
		cout << redcolor << " |1) Obtain data on a single stock from one group?                  |" << endl;
		cout << greencolor << " |2) Show the AAR and CAAR for the entirety of one group?           |" << endl;
		cout << bluecolor << " |3) Plot the Excel chart for CAAR of all 3 groups?                 |" << endl;
		cout << lredcolor << " |4) Quit?                                                          |" << endl << defcolor;
		cout << " --------------------------------------------------------------------" << endl;
		cout << endl;
		cout << "Which menu option would you like to see? Please enter the corresponding number: "; cin >> c;
		if (c.compare(string("1")) == 0)
		{
			ShowStockInfo(Beat, Meet, Miss);
			cout << endl; cout << endl; cout << endl;
			goto CheckPoint;
		}
		else if (c.compare(string("2")) == 0)
		{
			ShowStat(ResultMatrix);
			cout << endl; cout << endl; cout << endl;
			goto CheckPoint;
		}
		else if (c.compare(string("3")) == 0)
		{
			ShowPic(ResultMatrix);
			cout << endl; cout << endl; cout << endl;
			goto CheckPoint;
		}
		else if (c.compare(string("4")) == 0)
			cout << "Quit." << endl;
		else
		{
			cout << "Please enter a valid number." << endl;
			cout << endl; cout << endl; cout << endl;
			goto CheckPoint;
		}

		cout << endl; cout << endl; cout << endl;
	}
}
void ShowStockInfo(const Group& Beat, const Group& Meet, const Group& Miss)
{
	cout << "You choose 1." << endl;
	string sticker;
	cout << "Enter the ticker: "; cin >> sticker;;

	map<string, Stock>::const_iterator itr1 = Beat.Content.find(sticker);
	if (itr1 != Beat.Content.end())
	{
		itr1->second.ExportData();
		cout << sticker << " information has been exported to Excel" << endl;
	}
		
	map<string, Stock>::const_iterator itr2 = Meet.Content.find(sticker);
	if (itr2 != Meet.Content.end())
	{
		itr2->second.ExportData();
		cout << sticker << " information has been exported to Excel" << endl;
	}
		
	map<string, Stock>::const_iterator itr3 = Miss.Content.find(sticker);
	if (itr3 != Miss.Content.end())
	{
		itr3->second.ExportData();
		cout << sticker << " information has been exported to Excel" << endl;
	}
			
}
void ShowStat(const vector<vector<vector<double>>>& ResultMatrix)
{
	cout << "You choose 2." << endl;
	int indicator1, indicator2, a, b;
	cout << "1.Show AAR." << endl;
	cout << "2.Show CAAR." << endl;
	cin >> indicator2;
	if (indicator2 != 1 && indicator2 != 2)
		cout << "Enter a valid number please." << endl;
	cout << "1.Show group Beat." << endl;
	cout << "2.Show group Meet." << endl;
	cout << "3.Show group Miss." << endl;
	cin >> indicator1;
	if (indicator1 != 1 && indicator1 != 2 && indicator1 != 3)
		cout << "Enter a valid number please." << endl;
	NumericMatrix<double, long> Data(1, DayNum);
	b = indicator1 - 1;
	a = indicator2 - 1;
	for (long i = 1; i <= DayNum; i++)
		Data(1, i) = ResultMatrix[b][a][i - 1];
	list<std::string> inforow;
	list<std::string> infocol;
	if (indicator2 == 1)
	{
		inforow.push_back("AAR");
	}
	else
	{
		inforow.push_back("CAAR");
	}
	for (int i = 0; i < DayNum; i++)
	{

		infocol.push_back("Day "+ to_string(i - 60));
	}
	
	vector<vector<string>>title;
	title = SetTitle();
	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);
	excel.AddMatrix(title[a][b], Data, inforow, infocol);
	if (indicator2 == 1 && indicator1 == 1)
	{
		cout << "AAR Information for Beat group has been exported to Excel" << endl;
	}
	else if (indicator2 == 1 && indicator1 == 2)
	{
		cout << "AAR Information for Meet group has been exported to Excel" << endl;
	}
	else if (indicator2 == 1 && indicator1 == 3)
	{
		cout << "AAR Information for Miss group has been exported to Excel" << endl;
	}
	else if (indicator2 == 2 && indicator1 == 1) {
		cout << "CAAR information for Beat group has been exported to Excel" << endl;
	}
	else if (indicator2 == 2 && indicator1 == 2) {
		cout << "CAAR information for Meet group has been exported to Excel" << endl;
	}
	else if (indicator2 == 2 && indicator1 == 3) {
		cout << "CAAR information for Miss group has been exported to Excel" << endl;
	}
}

void ShowPic(const vector<vector<vector<double>>>& ResultMatrix)
{
	cout << "You choose 3." << endl;
	Vector<double, long> CAARx1(DayNum);
	Vector<double, long> CAARx2(DayNum);
	Vector<double, long> CAARx3(DayNum);
	Vector<double, long> CAARy1(DayNum);
	Vector<double, long> CAARy2(DayNum);
	Vector<double, long> CAARy3(DayNum);
	CAARx1[CAARx1.MinIndex()] = -60.0;
	CAARx2[CAARx2.MinIndex()] = -60.0;
	CAARx3[CAARx3.MinIndex()] = -60.0;
	for (long i = CAARx1.MinIndex() + 1; i <= CAARx1.MaxIndex(); i++)
	{
		CAARx1[i] = CAARx1[i - 1] + 1;
		CAARx2[i] = CAARx2[i - 1] + 1;
		CAARx3[i] = CAARx3[i - 1] + 1;
	}

	for (long i = CAARy1.MinIndex(); i <= CAARy1.MaxIndex(); i++)
	{
		CAARy1[i] = ResultMatrix[0][1][i - 1];
		CAARy2[i] = ResultMatrix[1][1][i - 1];
		CAARy3[i] = ResultMatrix[2][1][i - 1];
	}

	list<std::string> labels;// Names of each vector
	list<Vector<double, long> > yyy;
	labels.push_back("Beat");
	labels.push_back("Meet");
	labels.push_back("Miss");

	yyy.push_back(CAARy1);
	yyy.push_back(CAARy2);
	yyy.push_back(CAARy3);
	cout << endl;
	cout << "CAAR Information for all 3 groups has been exported to Excel" << endl;
	printInExcel(CAARx1, labels, yyy, "CAAR", "Days", "Abnormal return");

}