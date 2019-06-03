#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;

int main(){

	ifstream fundMode;
	ifstream secMode;
	ifstream combMode;
	fundMode.open("scope_3.csv");	//Fundamental Mode
	secMode.open("scope_5.csv");	//Second Order Mode
	combMode.open("scope_1.csv");	//Combined Mode

	double fundArr[1001];
	double secArr[1001];
	double combArr[1001];

	double fundIn[1001];
	double secIn[1001];
	double combIn[1001];

	double fundArrAvg[1001];
	double secArrAvg[1001];
	double combArrAvg[1001];

	char tempLine[100];
	string tempString;
	double tempFloat;
	int tempIndex = 0;

	int j = 0;
	fundMode.getline(tempLine, 100);
	fundMode.getline(tempLine, 100);
	while(j < 1000){
		fundMode.getline(tempLine, 100);
		tempString = tempLine;
		//cout<<tempString<<endl;
		tempIndex = tempString.find_last_of(",");
		fundArr[j] = stod(tempString.substr(tempIndex + 1));
		fundIn[j] = stod(tempString.substr(0, tempIndex));		
		//cout<<fundIn[j]<<",";
		//cout<<fundArr[j]<<endl;
		j++;
	}
	fundMode.close();

	j = 0;
	secMode.getline(tempLine, 100);
	secMode.getline(tempLine, 100);
	while(j < 1000){
		secMode.getline(tempLine, 100);
		tempString = tempLine;
		//cout<<tempString<<endl;
		tempIndex = tempString.find_last_of(",");
		secArr[j] = stod(tempString.substr(tempIndex + 1));
		secIn[j] = stod(tempString.substr(0, tempIndex));		
		//cout<<secIn[j]<<",";
		//cout<<secArr[j]<<endl;
		j++;
	}
	secMode.close();

	j = 0;
	combMode.getline(tempLine, 100);
	combMode.getline(tempLine, 100);
	while(j < 1000){
		combMode.getline(tempLine, 100);
		tempString = tempLine;
		//cout<<tempString<<endl;
		tempIndex = tempString.find_last_of(",");
		combArr[j] = stod(tempString.substr(tempIndex + 1));
		combIn[j] = stod(tempString.substr(0, tempIndex));		
		//cout<<combIn[j]<<",";
		//cout<<combArr[j]<<endl;
		j++;
	}
	combMode.close();

	ofstream fundFile;
	fundFile.open("fundFile.csv");
	ofstream secFile;
	secFile.open("secFile.csv");
	ofstream combFile;
	combFile.open("combFile.csv");
	ofstream bestFile;
	bestFile.open("bestFile.csv");

	int tempInt = 0;
	double avgArr[50];
	double tempVal = 0;
	double avg = 0;
	
	std::ostringstream streamObj;
	streamObj.precision(10);

////////FUND FILE/////////
	for(int i = 0; i < 50; i++){
		avgArr[i] = 0;
	}
	for(int i = 0; i < 1000; i++){
		tempVal = avgArr[tempInt];
		//cout<<tempVal<<",";
		avgArr[tempInt] = fundArr[i];
		//cout<<avgArr[tempInt]<<",";
		avg += ((avgArr[tempInt] - tempVal) /50);
		fundArrAvg[i] = avg;
		//cout<<fundArrAvg[i]<<endl;
		tempInt = (tempInt == 49 ? 0 : tempInt+1);
	}

	for(int i = 0; i < 1000; i++){
		streamObj.str("");
		streamObj.clear();
		streamObj<<fundIn[i];
		fundFile<<streamObj.str()<<",";

		streamObj.str("");
		streamObj.clear();
		streamObj<<fundArr[i];
		fundFile<<streamObj.str()<<",";
		
		streamObj.str("");
		streamObj.clear();
		streamObj<<fundArrAvg[i];
		fundFile<<streamObj.str()<<endl;
	}
	fundFile.close();

//////SEC FILE///////
	for(int i = 0; i < 50; i++){
		avgArr[i] = 0;
	}
	for(int i = 0; i < 1000; i++){
		tempVal = avgArr[tempInt];
		//cout<<tempVal<<",";
		avgArr[tempInt] = secArr[i];
		//cout<<avgArr[tempInt]<<",";
		avg += ((avgArr[tempInt] - tempVal) /50);
		secArrAvg[i] = avg;
		//cout<<secArrAvg[i]<<endl;
		tempInt = (tempInt == 49 ? 0 : tempInt+1);
	}

	for(int i = 0; i < 1000; i++){
		streamObj.str("");
		streamObj.clear();
		streamObj<<secIn[i];
		secFile<<streamObj.str()<<",";

		streamObj.str("");
		streamObj.clear();
		streamObj<<secArr[i];
		secFile<<streamObj.str()<<",";
		
		streamObj.str("");
		streamObj.clear();
		streamObj<<secArrAvg[i];
		secFile<<streamObj.str()<<endl;
	}
	secFile.close();

////////COMB FILE////////
	for(int i = 0; i < 50; i++){
		avgArr[i] = 0;
	}
	for(int i = 0; i < 1000; i++){
		tempVal = avgArr[tempInt];
		//cout<<tempVal<<",";
		avgArr[tempInt] = combArr[i];
		//cout<<avgArr[tempInt]<<",";
		avg += ((avgArr[tempInt] - tempVal) /50);
		combArrAvg[i] = avg;
		//cout<<combArrAvg[i]<<endl;
		tempInt = (tempInt == 49 ? 0 : tempInt+1);
	}

	for(int i = 0; i < 1000; i++){
		streamObj.str("");
		streamObj.clear();
		streamObj<<combIn[i];
		combFile<<streamObj.str()<<",";

		streamObj.str("");
		streamObj.clear();
		streamObj<<combArr[i];
		combFile<<streamObj.str()<<",";
		
		streamObj.str("");
		streamObj.clear();
		streamObj<<combArrAvg[i];
		combFile<<streamObj.str()<<endl;
	}
	combFile.close();


	

	double cost = 0;
	double costsMagUp = 0;
	double costfMagUp = 0;
	double costsOffUp = 0;
	double costfOffUp = 0;
	double costsMagDown = 0;
	double costfMagDown = 0;
	double costsOffDown = 0;
	double costfOffDown = 0;
	int closest1 = 0;
	int closest2 = 0;
	int closest3 = 0;

	double lowestCost = INT_MAX;
	double fundMagBest = 0;
	double secMagBest = 0;
	double fundOffBest = 0;
	double secOffBest = 0;
	
	double fundMagT = 0;
	double secMagT = 0;
	int fundOffT = 0;
	int secOffT = 0;

	double newMode[1001];
	for(int i = 0; i < 1001; i++){
		newMode[i] = 0;
	}

	int secOff = 1;
	int fundOff = 1;
	double secMag = 1;
	double fundMag = 1;

	double fundOffChange = 0;
	double secOffChange = 0;
	double fundMagChange = 0;
	double secMagChange = 0;
	int fundOffTemp = 0;
	int secOffTemp = 0;


/////////PASS 1///////////
	for(secOff = -500; secOff < 500; secOff+=20){
		cout<<"New Off: "<<secOff<<","<<cost<<endl;
		for(fundOff = -500; fundOff < 500; fundOff+=20){
			for(secMag = 0; secMag < 3; secMag +=0.2){
				for(fundMag = 0; fundMag < 3; fundMag +=0.2){
					cost = 0;
					for(int i = 0; i < 1000; i++){
						if(i+fundOff > 999){
							fundOffTemp = 999-i;
						}
						if(i+fundOff < 0){
							fundOffTemp = -1*i;
						}
						if(i+secOff > 999){
							secOffTemp = 999-i;
						}
						if(i+secOff < 0){
							secOffTemp = -1*i;
						}
						newMode[i] = 0.5 * (fundMag*fundArrAvg[i+fundOffTemp] 
											+ secMag*secArrAvg[i+secOffTemp]);
						cost+= (newMode[i] - combArrAvg[i]) * (newMode[i] - combArrAvg[i]);
					}
					if(cost < lowestCost){
						lowestCost = cost;
						secOffBest = secOff;
						fundOffBest = fundOff;
						secMagBest = secMag;
						fundMagBest = fundMag;
						cout<<"Lowest: "<<secOffBest<<","<<fundOffBest<<","<<secMagBest<<","
							<<fundMagBest<<": "<<lowestCost<<endl;
					}
				}
			}
		}
	}
	

//////////PASS 2///////////
	fundMagT = fundMagBest;
	secMagT = secMagBest;
	fundOffT = fundOffBest;
	secOffT = secOffBest;

	cout<<endl<<endl<<"Pass 2"<<endl;
	for(secOff = secOffT-50; secOff < secOffT+50; secOff+=5){
	cout<<"New Off: "<<secOff<<","<<cost<<endl;
		for(fundOff = fundOffT-50; fundOff < fundOffT+50; fundOff+=5){
			for(secMag = secMagT-0.5; secMag < secMagT+0.5; secMag +=0.05){
				for(fundMag = fundMagT-0.5; fundMag < fundMagT+0.5; fundMag +=0.05){
					cost = 0;
					for(int i = 0; i < 1000; i++){
						if(i+fundOff > 999){
							fundOffTemp = 999-i;
						}
						if(i+fundOff < 0){
							fundOffTemp = -1*i;
						}
						if(i+secOff > 999){
							secOffTemp = 999-i;
						}
						if(i+secOff < 0){
							secOffTemp = -1*i;
						}
						newMode[i] = 0.5 * (fundMag*fundArrAvg[i+fundOffTemp] 
											+ secMag*secArrAvg[i+secOffTemp]);
						cost+= (newMode[i] - combArrAvg[i]) * (newMode[i] - combArrAvg[i]);
					}
					if(cost < lowestCost){
						lowestCost = cost;
						secOffBest = secOff;
						fundOffBest = fundOff;
						secMagBest = secMag;
						fundMagBest = fundMag;
						cout<<"Lowest: "<<secOffBest<<","<<fundOffBest<<","<<secMagBest<<","
							<<fundMagBest<<": "<<lowestCost<<endl;
					}
				}
			}
		}
	}
	

/////////PASS 3///////
	fundMagT = fundMagBest;
	secMagT = secMagBest;
	fundOffT = fundOffBest;
	secOffT = secOffBest;

	cout<<endl<<endl<<"Pass 3"<<endl;
	for(secOff = secOffT-20; secOff < secOffT+20; secOff+=1){
	cout<<"New Off: "<<secOff<<","<<cost<<endl;
		for(fundOff = fundOffT-20; fundOff < fundOffT+20; fundOff+=1){
			for(secMag = secMagT-0.2; secMag < secMagT+0.2; secMag +=0.01){
				for(fundMag = fundMagT-0.2; fundMag < fundMagT+0.2; fundMag +=0.01){
					cost = 0;
					for(int i = 0; i < 1000; i++){
						if(i+fundOff > 999){
							fundOffTemp = 999-i;
						}
						if(i+fundOff < 0){
							fundOffTemp = -1*i;
						}
						if(i+secOff > 999){
							secOffTemp = 999-i;
						}
						if(i+secOff < 0){
							secOffTemp = -1*i;
						}
						newMode[i] = 0.5 * (fundMag*fundArrAvg[i+fundOffTemp] 
											+ secMag*secArrAvg[i+secOffTemp]);
						cost+= (newMode[i] - combArrAvg[i]) * (newMode[i] - combArrAvg[i]);
					}
					if(cost < lowestCost){
						lowestCost = cost;
						secOffBest = secOff;
						fundOffBest = fundOff;
						secMagBest = secMag;
						fundMagBest = fundMag;
						cout<<"Lowest Cost: "<<secOffBest<<","<<fundOffBest<<","<<secMagBest<<","
							<<fundMagBest<<": "<<lowestCost<<endl;
					}
				}
			}
		}
	}
	

	cout<<endl<<endl<<"FINAL LOWEST COST: "<<lowestCost<<endl;
	cout<<"Best Second Order Offset: "<<secOffBest<<endl;
	cout<<"Best First Order Offset: "<<fundOffBest<<endl;
	cout<<"Best Second Order Magnitude: "<<(secMagBest/(secMagBest+fundMagBest))<<endl;
	cout<<"Best First Order Magnitude: "<<(fundMagBest/(secMagBest+fundMagBest))<<endl;

	///////New ARRAY FOR BEST FIT////////
	for(int i = 0; i < 1000; i++){
		if(i+fundOffBest > 999){
			fundOffTemp = 999-i;
			}
			if(i+fundOffBest < 0){
				fundOffTemp = -1*i;
			}
			if(i+secOffBest > 999){
				secOffTemp = 999-i;
			}
			if(i+secOffBest < 0){
				secOffTemp = -1*i;
			}
			newMode[i] = 0.5 * (fundMagBest*fundArrAvg[i+fundOffTemp] 
								+ secMagBest*secArrAvg[i+secOffTemp]);
	}

	//////////BEST FIT FILE///////////
	for(int i = 0; i < 1000; i++){
		streamObj.str("");
		streamObj.clear();
		streamObj<<combIn[i];
		bestFile<<streamObj.str()<<",";

		streamObj.str("");
		streamObj.clear();
		streamObj<<combArr[i];
		bestFile<<streamObj.str()<<",";
		
		streamObj.str("");
		streamObj.clear();
		streamObj<<combArrAvg[i];
		bestFile<<streamObj.str()<<",";

		streamObj.str("");
		streamObj.clear();
		streamObj<<newMode[i];
		bestFile<<streamObj.str()<<endl;
	}

	bestFile<<endl<<endl<<"FINAL LOWEST COST: "<<lowestCost<<endl;
	bestFile<<"Best Second Order Offset: "<<secOffBest<<endl;
	bestFile<<"Best First Order Offset: "<<fundOffBest<<endl;
	bestFile<<"Best Second Order Magnitude: "<<(secMagBest/(secMagBest+fundMagBest))<<endl;
	bestFile<<"Best First Order Magnitude: "<<(fundMagBest/(secMagBest+fundMagBest))<<endl;
	bestFile.close();

	return 0;
}