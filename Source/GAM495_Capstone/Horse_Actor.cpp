// Fill out your copyright notice in the Description page of Project Settings.


#include "Horse_Actor.h"
//#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"  // for random integers

// Sets default values
AHorse_Actor::AHorse_Actor()
{
	// instantiate mesh object
	horseMesh = CreateDefaultSubobject<UStaticMeshComponent>("horse mesh");
	RootComponent = horseMesh;

	// genes default to EeAa
	eGenes[0] = 69;
	eGenes[1] = 101;
	aGenes[0] = 65;
	aGenes[1] = 97;

	// coat defaults to black KK
	// conflicts with default genes on purpose
	horseCoat[0] = 'K';
	horseCoat[1] = 'K';

	// deafult material color
	coatLinearColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
}

void AHorse_Actor::setMaterial(char coatColor[2])
{
	// assigns coatLinearColor to some color based on coat genes
	if (coatColor[0] == 'K')  // black
	{
		coatLinearColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
	}
	else if (coatColor[0] == 'C')  // chestnut
	{
		switch (coatColor[1])
		{
		case 'L':  // light chestnut -> CL
			//coatLinearColor = FLinearColor(0.201f, 0.142f, 0.92f, 1.f);
			coatLinearColor = FLinearColor(0.79f, 0.56f, 0.36f, 1.f);
			break;
		case 'P':  // pale chestnut -> CP
			//coatLinearColor = FLinearColor(0.152f, 0.111f, 0.80f, 1.f);
			coatLinearColor = FLinearColor(0.6f, 0.44f, 0.31f, 1.f);
			break;
		case 'R':  // liver chestnut -> CR
			//coatLinearColor = FLinearColor(0.39f, 0.21f, 0.13f, 1.f);
			coatLinearColor = FLinearColor(0.15f, 0.08f, 0.05f, 1.f);
			break;
		case 'S':  // sorrel -> CS
			//coatLinearColor = FLinearColor(0.124f, 0.55f, 0.26f, 1.f);
			coatLinearColor = FLinearColor(0.49f, 0.22f, 0.1f, 1.f);
			break;
		case 'G':  // golden chestnut -> CG
			//coatLinearColor = FLinearColor(0.201f, 0.151f, 0.74f, 1.f);
			coatLinearColor = FLinearColor(0.79f, 0.59f, 0.29f, 1.f);
			break;
		case 'B':  // bright chestnut -> CB
			//coatLinearColor = FLinearColor(0.164f, 0.75f, 0.15f, 1.f);
			coatLinearColor = FLinearColor(0.64f, 0.29f, 0.06f, 1.f);
			break;
		case 'M':  // medium chestnut -> CM
			//coatLinearColor = FLinearColor(0.155f, 0.75f, 0.32f, 1.f);
			coatLinearColor = FLinearColor(0.61f, 0.29f, 0.13f, 1.f);
			break;
		case 'C':  // copper chestnut -> CC
			//coatLinearColor = FLinearColor(0.173f, 0.90f, 0.26f, 1.f);
			coatLinearColor = FLinearColor(0.68f, 0.35f, 0.1f, 1.f);
			break;
		default:  // defaults to black
			coatLinearColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
			break;
		}
	}
	else  // bay
	{
		switch (coatColor[1])
		{
		case 'W':  // wild bay -> BW
			//coatLinearColor = FLinearColor(0.115f, 0.59f, 0.37f, 1.f);
			coatLinearColor = FLinearColor(0.45f, 0.23f, 0.15f, 1.f);
			break;
		case 'S':  // seal brown -> BS
			//coatLinearColor = FLinearColor(0.33f, 0.21f, 0.16f, 1.f);
			coatLinearColor = FLinearColor(0.13f, 0.08f, 0.06f, 1.f);
			break;
		case 'M':  // mahogany bay -> BM
			//coatLinearColor = FLinearColor(0.64f, 0.20f, 0.13f, 1.f);
			coatLinearColor = FLinearColor(0.25f, 0.07f, 0.05f, 1.f);
			break;
		case 'D':  // dark bay -> BD
			//coatLinearColor = FLinearColor(0.64f, 0.32f, 0.13f, 1.f);
			coatLinearColor = FLinearColor(0.25f, 0.13f, 0.05f, 1.f);
			break;
		case 'G':  // golden bay -> BG
			//coatLinearColor = FLinearColor(0.179f, 0.119f, 0.52f, 1.f);
			coatLinearColor = FLinearColor(0.7f, 0.47f, 0.2f, 1.f);
			break;
		case 'L':  // light bay -> BL
			//coatLinearColor = FLinearColor(0.134f, 0.85f, 0.56f, 1.f);
			coatLinearColor = FLinearColor(0.53f, 0.3f, 0.22f, 1.f);
			break;
		case 'B':  // blood bay -> BB
			//coatLinearColor = FLinearColor(0.182f, 0.73f, 0.21f, 1.f);
			coatLinearColor = FLinearColor(0.71f, 0.29f, 0.08f, 1.f);
			break;
		case 'Y':  // cherry bay -> BY
			//coatLinearColor = FLinearColor(0.182f, 0.68f, 0.21f, 1.f);
			coatLinearColor = FLinearColor(0.71f, 0.27f, 0.08f, 1.f);
			break;
		case 'C':  // classic bay -> BC
			//coatLinearColor = FLinearColor(0.161f, 0.87f, 0.45f, 1.f);
			coatLinearColor = FLinearColor(0.63f, 0.34f, 0.18f, 1.f);
			break;
		case 'R':  // copper bay -> BR
			//coatLinearColor = FLinearColor(0.161f, 0.92f, 0.26f, 1.f);
			coatLinearColor = FLinearColor(0.63f, 0.36f, 0.1f, 1.f);
			break;
		default:  // defaults to black
			coatLinearColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
			break;
		}
	}

	// terminal message
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("FLinearColor = %s"), *coatLinearColor.ToString()));
	}

	// applies coatLinearColor to coatDMI
	// parameter name "coatColor" set in Editor
	coatDMI->SetVectorParameterValue("coatColor", coatLinearColor);
	//coatDMI->SetTextureParameterValue("coatColor", coatTexture);

	// applies coatLinearColor to the actor's material
	horseMesh->SetMaterial(0, coatDMI);
}

// Called when the game starts or when spawned
void AHorse_Actor::BeginPlay()
{
	Super::BeginPlay();

	// sets up material
	// cannot be inside constructor because Editor crashes:
	// NewObject with empty name can't be used to create default subobjects (inside of UObject derived class constructor) as it produces inconsistent object names. Use ObjectInitializer.CreateDefaultSubobject<> instead.
	coatDMI = UMaterialInstanceDynamic::Create(coatMAT, this);

	// generates genecodes
	AHorse_Actor::generateGenes();

	// generates horseCoat
	AHorse_Actor::generateCoat();

	// applies correct material color to actor
	setMaterial(horseCoat);
}

void AHorse_Actor::generateGenes()
{
	/*
	* genetic number system, taken from the decimal unicode of the letter
	* E -> 69
	* e -> 101
	* A -> 65
	* a -> 97
	* At -> 116
	* A+ -> 43
	*/

	// assigns eGenes and aGenes arrays' numerical values
	for (int i = 0; i < 2; ++i)
	{
		int E = UKismetMathLibrary::RandomIntegerInRange(0, 1);

		// assigns correct Extension value
		if (E == 0) {
			eGenes[i] = 69;
		}
		else {
			eGenes[i] = 101;
		}

		int A = 0;
		bool bA = false;  // if agouti has been assigned

		// decides if Agouti will be At or A+
		int AtChance = UKismetMathLibrary::RandomIntegerInRange(0, 100);
		int ApChance = UKismetMathLibrary::RandomIntegerInRange(0, 100);
		if (AtChance <= 5) {
			aGenes[i] = 116;
			bA = true;
		}
		else if (ApChance <= 50) {
			aGenes[i] = 43;
			bA = true;
		}
		else {
			A = UKismetMathLibrary::RandomIntegerInRange(0, 1);
		}

		// assigns correct Agouti value
		if (!bA) {
			if (A == 0)
			{
				aGenes[i] = 65;
			}
			else
			{
				aGenes[i] = 97;
			}
		}
	}

	// prints unsorted genes to viewport
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("eGenes[0] = %s, eGenes[1] = %s"), &eGenes[0], &eGenes[1]));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("aGenes[0] = %s, aGenes[1] = %s"), &aGenes[0], &aGenes[1]));
	}

	/*
	* sorts eGenes and aGenes
	* illegal gene pairings include:
	* eE
	* aA
	* AtA
	* _A+
	*/

	// local variables to store genes
	int domE = 0;
	int recE = 0;
	int domA = 0;
	int recA = 0;

	if (eGenes[0] > eGenes[1]) {  // eE instead of Ee
		domE = 69;
		recE = 101;
	}

	if (aGenes[0] != aGenes[1])  // negates change if genes are the same
	{
		if (aGenes[0] > aGenes[1]) {  // aA, aA+, AA+, Ata, AtA, or AtA+
			// swaps genes
			domA = aGenes[1];
			recA = aGenes[0];
			// options are now
			// Aa, A+a, A+A, aAt, AAt, or A+At

			// swaps aAt to Ata
			if (domA == 97) {
				domA = 116;
				recA = 97;
			}
		}
		else {  // A+A, A+a, A+At, Aa, AAt, aAt
			// swaps aAt to Ata
			if (aGenes[0] == 97) {
				domA = 116;
				recA = 97;
			}
		}
	}

	// reassign arrays if genes have been swapped
	if (domE != 0)
	{
		eGenes[0] = domE;
	}
	if (recE != 0)
	{
		eGenes[1] = recE;
	}
	if (domA != 0)
	{
		aGenes[0] = domA;
	}
	if (recA != 0)
	{
		aGenes[1] = recA;
	}

	// prints sorted genes to viewport
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("eGenes[0] = %s, eGenes[1] = %s"), &eGenes[0], &eGenes[1]));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("aGenes[0] = %s, aGenes[1] = %s"), &aGenes[0], &aGenes[1]));
	}
}

void AHorse_Actor::generateCoat()
{
	/*
	* assigns first index in coat array
	* black -> K
	* chestnut -> C
	* bay -> B
	*/
	if (eGenes[0] == 101) {  // ee__
		horseCoat[0] = 'C';
	}
	else {
		if (aGenes[0] == 97) {  // E_aa
			horseCoat[0] = 'K';
		}
		else {  // E_A_
			horseCoat[0] = 'B';
		}
	}

	// assigns second index in coat array
	if (horseCoat[0] == 'K')  // black
	{
		horseCoat[1] = 'K';  // black

		// prints coat identifiers to viewport
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = KK; black"), &horseCoat));
		}
	}
	else if (horseCoat[0] == 'C')  // chestnut
	{
		/*
		*	light chestnut -> CL
		*	pale chestnut -> CP
		*	liver chestnut -> CR
		*	sorrel -> CS
		*	golden chestnut -> CG
		*	bright chestnut -> CB
		*	medium chestnut -> CM
		*	copper chestnut -> CC
		*/
		if (aGenes[0] == 43) {  // A+_
			if (UKismetMathLibrary::RandomIntegerInRange(0, 100) <= 50) {
				horseCoat[1] = 'L';  // light chestnut

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CL; light chestnut"), &horseCoat));
				}
			}
			else {
				horseCoat[1] = 'P';  // pale chestnut

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CP; pale chestnut"), &horseCoat));
				}
			}
		}
		else {
			if (aGenes[0] == 97) {  // aa
				horseCoat[1] = 'R';  // liver chestnut

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CR; liver chestnut"), &horseCoat));
				}
			}
			else if (aGenes[1] == 65) {  // AA
				if (UKismetMathLibrary::RandomIntegerInRange(0, 100) <= 20) {
					horseCoat[1] = 'S';  // sorrel

					// prints coat identifiers to viewport
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CS; sorrel"), &horseCoat));
					}
				}
			}
			else if (aGenes[0] == 116) {  // AtAt, Ata
				if (UKismetMathLibrary::RandomIntegerInRange(0, 100) <= 10) {
					horseCoat[1] = 'G';  // golden chestnut

					// prints coat identifiers to viewport
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CG; golden chestnut"), &horseCoat));
					}
				}
			}
		}
		// all other coat attempts failed
		if (horseCoat[1] == 'K')
		{
			int coatChance = UKismetMathLibrary::RandomIntegerInRange(0, 2);
			if (coatChance == 0) {
				horseCoat[1] = 'B';  // bright chestnut

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CB; bright chestnut"), &horseCoat));
				}
			}
			else if (coatChance == 1) {
				horseCoat[1] = 'M';  // medium chestnut

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CM; medium chestnut"), &horseCoat));
				}
			}
			else {
				horseCoat[1] = 'C';  // copper chestnut

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = CC; copper chestnut"), &horseCoat));
				}
			}
		}
	}
	else  // bay
	{
		/*
		* Bay -> B
		*	wild bay -> BW
		*	seal brown -> BS
		*	mahogany bay -> BM
		*	dark bay -> BD
		*	golden bay -> BG
		*	light bay -> BL
		*	blood bay -> BB
		*	cherry bay -> BY
		*	classic bay -> BC
		*	copper bay -> BR
		*/
		if (aGenes[0] == 43) {  // A+_
			horseCoat[1] = 'W';  // wild bay

			// prints coat identifiers to viewport
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BW; wild bay"), &horseCoat));
			}
		}
		else {
			if (aGenes[0] == 116) {  // AtAt, Ata
				horseCoat[1] = 'S';  // seal brown

				// prints coat identifiers to viewport
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BS; seal brown"), &horseCoat));
				}
			}
			else {  // AA, Aa, AAt
				if (aGenes[1] != 116) {  // AA, Aa
					if (eGenes[1] == 69) {  // EEAA, EEAa
						if (UKismetMathLibrary::RandomIntegerInRange(0, 100) <= 50) {
							if (aGenes[1] == 65) {  // EEAA
								horseCoat[1] = 'M';  // mahogany bay
								// prints coat identifiers to viewport
								if (GEngine)
								{
									GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BM; mahogany bay"), &horseCoat));
								}
							}
							else {  // EEAa
								horseCoat[1] = 'D';  // dark bay

								// prints coat identifiers to viewport
								if (GEngine)
								{
									GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BD; dark bay"), &horseCoat));
								}
							}
						}
					}
					else {  // EeAA, EeAa
						int coatChance = UKismetMathLibrary::RandomIntegerInRange(0, 100);
						if (aGenes[1] == 65) {  // EeAA
							if (coatChance <= 60) {
								if (coatChance <= 10) {
									horseCoat[1] = 'G';  // golden bay

									// prints coat identifiers to viewport
									if (GEngine)
									{
										GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BG; golden bay"), &horseCoat));
									}
								}
								else {
									horseCoat[1] = 'L';  // light bay

									// prints coat identifiers to viewport
									if (GEngine)
									{
										GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BL; light bay"), &horseCoat));
									}
								}
							}
						}
						else {  // EeAa
							if (coatChance <= 60) {
								if (coatChance <= 10) {
									horseCoat[1] = 'B';  // blood bay

									// prints coat identifiers to viewport
									if (GEngine)
									{
										GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BB; blood bay"), &horseCoat));
									}
								}
								else {
									horseCoat[1] = 'Y';  // cherry bay

									// prints coat identifiers to viewport
									if (GEngine)
									{
										GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BY; cherry bay"), &horseCoat));
									}
								}
							}
						}
					}
				}
			}
			if (horseCoat[1] == 'K')
			{
				// all other coat attempts failed
				int coatChance = UKismetMathLibrary::RandomIntegerInRange(0, 1);
				if (coatChance == 0) {
					horseCoat[1] = 'C';  // classic bay

					// prints coat identifiers to viewport
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BC; classic bay"), &horseCoat));
					}
				}
				else {
					horseCoat[1] = 'R';  // copper bay

					// prints coat identifiers to viewport
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("horseCoat = BR; copper bay"), &horseCoat));
					}
				}
			}
		}
	}
}

