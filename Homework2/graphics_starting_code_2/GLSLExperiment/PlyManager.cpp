#include "PlyManager.h"

void PlyManager::LoadPlyFiles()
{
	bool loadAll = !this->devMode;

	if (loadAll)
	{
		cout << "Loading all ply files. This may take some time..." << endl;

		this->createPly("cube.ply");
		this->createPly("airplane.ply");
		this->createPly("ant.ply");
		this->createPly("apple.ply");
		this->createPly("balance.ply");
		this->createPly("beethoven.ply");
		this->createPly("big_atc.ply");
		this->createPly("big_dodge.ply");
		this->createPly("big_porsche.ply");
		this->createPly("big_spider.ply");
		this->createPly("canstick.ply");
		this->createPly("chopper.ply");
		this->createPly("cow.ply");
		this->createPly("dolphins.ply");
		this->createPly("egret.ply");
		this->createPly("f16.ply");
		this->createPly("footbones.ply");
		this->createPly("fracttree.ply");
		this->createPly("galleon.ply");
		this->createPly("hammerhead.ply");
		this->createPly("helix.ply");
		this->createPly("hind.ply");
		this->createPly("kerolamp.ply");
		this->createPly("ketchup.ply");
		this->createPly("mug.ply");
		this->createPly("part.ply");
		this->createPly("pickup_big.ply");
		this->createPly("pump.ply");
		this->createPly("pumpa_tb.ply");
		this->createPly("sandal.ply");
		this->createPly("saratoga.ply");
		this->createPly("scissors.ply");
		this->createPly("shark.ply");
		this->createPly("steeringweel.ply");
		this->createPly("stratocaster.ply");
		this->createPly("street_lamp.ply");
		this->createPly("teapot.ply");
		this->createPly("tennis_shoe.ply");
		this->createPly("tommygun.ply");
		this->createPly("trashcan.ply");
		this->createPly("turbine.ply");
		this->createPly("urn2.ply");
		this->createPly("walkman.ply");		
		this->createPly("weathervane.ply");
	}
	else
	{
		cout << "Loading all dev ply files. This may take some time..." << endl;

		this->createPly("cube.ply");
		this->createPly("cow.ply");
		this->createPly("hammerhead.ply");
		this->createPly("tommygun.ply");
	}

	cout << "plyManager loaded up: " << this->polygons.size() << " polygons" << endl;
}

Ply PlyManager::GetCurrentPly() 
{
	int current = this->currentPly;
	vector<Ply> currentPlys = this->polygons;
	Ply currentPly = currentPlys[current];

	if (!currentPly.LoadGeometry())
	{
		cout << "ERROR!!! Failed to load geometry for polygon: " << currentPly.getFilename() << endl;
	}

	return currentPly;
}

Ply PlyManager::GetNextPly()
{
	++this->currentPly;
	if (this->currentPly >= this->polygons.size())
	{
		this->currentPly = 0;
	}

	return this->GetCurrentPly();
}

Ply PlyManager::GetPreviousPly()
{
	--this->currentPly;
	if (this->currentPly < 0)
	{
		this->currentPly = this->polygons.size() - 1;
	}

	return this->GetCurrentPly();
}

void PlyManager::createPly(string filename)
{
	Ply *polygon = new Ply(this->program, filename);

	if (polygon->LoadGeometry())
	{
		this->polygons.push_back(*polygon);
	}
	else
	{
		cout << "ERROR!!! Failed to load geometry for polygon: " << polygon->getFilename() << endl;
	}
}

