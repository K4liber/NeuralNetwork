void entropyGromg(){
	ifstream signal;
	signal.open("entropyLogistic.txt");
	double valSignal;

	int iteracja=0;
	double g=3.5;

	TGraph *signalGraph = new TGraph();	

	while(signal>>valSignal){
		signalGraph->SetPoint(iteracja, g, valSignal);
		iteracja++;
		g+=0.0005;
	}
	signal.close();

	signalGraph->SetTitle("Entropy from g");
	signalGraph->GetXaxis()->SetTitle("Entropy");
	signalGraph->GetYaxis()->SetTitle("g");

	TCanvas *c1 = new TCanvas("c1","Lab1",10,10,800,800);
	c1->Divide(1,1);
	c1->cd(1);
	signalGraph->Draw();
	
	/*
	leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->SetHeader("The Legend Title");
	leg->AddEntry("gr","Graph with error bars","lep");
	leg->Draw();
	*/

	c1->update();
}
