#include "Translator.h"

void Translator::AddXaxisTranslation()
{
	bool positive = this->positiveX;
	bool negative = this->negativeX;

	if (positive && negative) return;
	if (positive) this->transformations.push_back(Angel::Translate(TRANSLATEINCREMENT, 0.0, 0.0));
	if (negative) this->transformations.push_back(Angel::Translate(TRANSLATEINCREMENT * -1, 0.0, 0.0));
}

void Translator::AddYaxisTranslation()
{
	bool positive = this->positiveY;
	bool negative = this->negativeY;

	if (positive && negative) return;
	if (positive) this->transformations.push_back(Angel::Translate(0.0, TRANSLATEINCREMENT, 0.0));
	if (negative) this->transformations.push_back(Angel::Translate(0.0, TRANSLATEINCREMENT * -1, 0.0));
}

void Translator::AddZaxisTranslation()
{
	bool positive = this->positiveZ;
	bool negative = this->negativeZ;

	if (positive && negative) return;
	if (positive) this->transformations.push_back(Angel::Translate(0.0, 0.0, TRANSLATEINCREMENT));
	if (negative) this->transformations.push_back(Angel::Translate(0.0, 0.0, TRANSLATEINCREMENT * -1));
}
