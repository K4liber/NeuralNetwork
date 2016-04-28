void drawAllGraphs(){
	ifstream variationX;
	ifstream variationY;
	variationX.open("variationX.txt");
	variationY.open("variationY.txt");
	double variationXVal;
	double variationYVal;

	int variationNumber=0;
	int helper=0;

	TGraph *variationGraph = new TGraph();
	
	while(variationX>>variationXVal){
		variationY>>variationYVal;
		if(!(helper%6)){
			variationGraph->SetPoint(variationNumber, variationXVal, variationYVal);
			variationNumber++;
		}
		helper++;
	}
	variationX.close();
	variationY.close();

	variationGraph->SetTitle("Network variation ( g=3.24 )");
	variationGraph->GetXaxis()->SetTitle("time");
	variationGraph->GetYaxis()->SetTitle("Variation");

	ifstream recX1;
	ifstream recY1;
	recX1.open("recX1.txt");
	recY1.open("recY1.txt");
	double recX1Val;
	double recY1Val;

	int recNumber=0;

	TGraph *recGraph = new TGraph();
	
	while(recX1>>recX1Val){
		recY1>>recY1Val;
		recGraph->SetPoint(recNumber, recX1Val, recY1Val);
		recNumber++;
	}
	recX1.close();
	recY1.close();

	recGraph->SetTitle("Recursive Diagram ( g=3.24 )");
	recGraph->GetXaxis()->SetTitle("f(t)");
	recGraph->GetYaxis()->SetTitle("f(t)");

	ifstream returnsMapX;
	ifstream returnsMapY;
	returnsMapX.open("returnsMapX.txt");
	returnsMapY.open("returnsMapY.txt");
	double returnsMapXVal;
	double returnsMapYVal;

	int returnsNumber=0;

	TGraph *returnsGraph = new TGraph();
	
	while(returnsMapX>>returnsMapXVal){
		returnsMapY>>returnsMapYVal;
		returnsGraph->SetPoint(returnsNumber, returnsMapXVal, returnsMapYVal);
		returnsNumber++;
	}
	returnsMapX.close();
	returnsMapY.close();

	returnsGraph->SetTitle("Map of returns ( g=3.24 )");
	returnsGraph->GetXaxis()->SetTitle("f(t)");
	returnsGraph->GetYaxis()->SetTitle("f(t+T)");
	
	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(2,2);
	c1->cd(1);
	variationGraph->Draw();
	c1->cd(2);
	recGraph->Draw("AP");
	c1->cd(3);
	returnsGraph->Draw("AP");
	recGraph->SetMarkerStyle(1);
	returnsGraph->SetMarkerStyle(8);
	//c1->update();
}
