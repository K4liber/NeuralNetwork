void makeGraphs(){
	ifstream recX;
	recX.open("recX.txt");
	ifstream recY;
	recY.open("recY.txt");
	ifstream returnsMapX;
	returnsMapX.open("returnsMapX.txt");
	ifstream returnsMapY;
	returnsMapY.open("returnsMapY.txt");

	double valRecX;
	double valRecY;
	double valReturnsMapX;
	double valReturnsMapY;

	int recPointNumber=0;
	int returnsPointNumber=0;

	TGraph *recGraph = new TGraph();
	TGraph *returnsGraph = new TGraph();	

	while(recX>>valRecX){
		recY>>valRecY;
		recGraph->SetPoint(recPointNumber, valRecX, valRecY);
		recPointNumber++;
	}
	recX.close();
	recY.close();

	while(returnsMapX>>valReturnsMapX){
		returnsMapY>>valReturnsMapY;
		returnsGraph->SetPoint(returnsPointNumber, valReturnsMapX, valReturnsMapY);
		returnsPointNumber++;
	}
	returnsMapX.close();
	returnsMapY.close();

	recGraph->SetTitle("Recursive diagram");
	recGraph->GetXaxis()->SetTitle("f(x)");
	recGraph->GetYaxis()->SetTitle("f(x)");

	returnsGraph->SetTitle("Map of returns");
	returnsGraph->GetXaxis()->SetTitle("f(x)");
	returnsGraph->GetYaxis()->SetTitle("f(x+T)");

	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(2,1);
	c1->cd(1);
	recGraph->Draw("AP");
	c1->cd(2);
	returnsGraph->Draw("AP");
	returnsGraph->SetMarkerStyle(8);
	
	/*
	leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->SetHeader("The Legend Title");
	leg->AddEntry("gr","Graph with error bars","lep");
	leg->Draw();
	*/

	c1->update();
}
