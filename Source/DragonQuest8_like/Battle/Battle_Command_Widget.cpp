// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Command_Widget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



UBattle_Command_Widget::UBattle_Command_Widget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), kougeki_button(nullptr)
{
	static ConstructorHelpers::FObjectFinder< USoundBase > find_sound(TEXT("/Script/Engine.SoundWave'/Game/DragonQuest8_like/Scenes/Battle/Select_SE.Select_SE'"));
	if (find_sound.Succeeded()) {
		Sound_Select = find_sound.Object;
	}

}

void UBattle_Command_Widget::NativeConstruct() {
	Super::NativeConstruct();
	//UE_LOG(LogTemp, Warning, TEXT("Output3: %s"), *HBox_Child->GetAllChildren()[i]->GetName());

	for (int32 index = 0; index < ENEMY_NUM_MAX; ++index) {
		FString str1 = "Enemy_Text" + FString::FromInt(index + 1);
		UTextBlock* tmp = Cast<UTextBlock>(GetWidgetFromName(FName(str1)));
		ensure(tmp != nullptr);
		if (tmp != nullptr)
		{
			enemy_texts.Add(tmp);
		}

		FString str2 = "Enemy_Button" + FString::FromInt(index + 1);
		UButton* button = Cast<UButton>(GetWidgetFromName(FName(str2)));
		ensure(button != nullptr);
		if (button != nullptr)
		{
			enemy_buttons.Add(button);
		}

		FString str3 = "Enemy_Num_Text" + FString::FromInt(index + 1);
		UTextBlock* text = Cast<UTextBlock>(GetWidgetFromName(FName(str3)));
		ensure(text != nullptr);
		if (text != nullptr)
		{
			enemy_num_texts.Add(text);
		}

	}

	Enemy_Infos_Init();
	Create_Enemy_UI();
	SpawnEnemy();

	UCanvasPanel* panel1 = Cast<UCanvasPanel>(GetWidgetFromName("Enemy_Panel"));
	ensure(panel1 != nullptr);
	if (panel1 != nullptr) {
		enemy_canvas = panel1;
	}


	UButton* Button = Cast<UButton>(GetWidgetFromName("Kougeki_Button"));
	ensure(Button != nullptr);
	if (Button != nullptr) {
		kougeki_button = Button;
	}

	if (!kougeki_button->OnClicked.IsBound()) {
		kougeki_button->OnClicked.AddDynamic(this, &UBattle_Command_Widget::Pressed_kougeki);
	}

	USpacer* spacer = Cast<USpacer>(GetWidgetFromName("Disable_Spacer"));
	ensure(spacer != nullptr);
	if (spacer != nullptr) {
		disable_spacer = spacer;
	}

	UCanvasPanel* panel2 = Cast<UCanvasPanel>(GetWidgetFromName("Party_Panel"));
	ensure(panel2 != nullptr);
	if (panel2 != nullptr) {
		party_canvas = panel2;
	}


}


void UBattle_Command_Widget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBattle_Command_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UBattle_Command_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBattle_Command_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBattle_Command_Widget::Create_Enemy_UI()
{

	for (int32 Index = 0; Index < enemy_num; ++Index)
	{
		if (enemy_texts[Index] != nullptr)
		{
			FSlateColor Color = FLinearColor::White;
			enemy_texts[Index]->SetColorAndOpacity(Color);
			FSlateFontInfo TextInfo = enemy_texts[Index]->GetFont();
			TextInfo.Size = FONT_SIZE;
			enemy_texts[Index]->SetFont(TextInfo);
			enemy_texts[Index]->SetText(Enemy_Infos[Index].NAME);
		}

	}
}

void UBattle_Command_Widget::Load_Enemy()
{
	FSoftObjectPath EnemyDataAssetPath = "/Script/DragonQuest8_like.EnemyDataAsset'/Game/DragonQuest8_like/Scenes/Field/EnemyDataAsset.EnemyDataAsset'";

	if (enemy_asset == nullptr)
	{
		enemy_asset = Cast<UEnemyDataAsset>(StaticLoadObject(UEnemyDataAsset::StaticClass(), nullptr, *EnemyDataAssetPath.ToString()));
		ensure(enemy_asset != nullptr);
	}
	return;
}

void UBattle_Command_Widget::Enemy_Infos_Init()
{
	Load_Enemy();
	enemy_num = FMath::RandRange(1, ENEMY_NUM_MAX);

	if (enemy_asset != nullptr)
	{
		UDQ8GameInstance* instance = UDQ8GameInstance::GetInstance();
		if (instance)
		{
			Enemy_Infos.Add(enemy_asset->Data[instance->enemy_id]);
		}
		
		for (int32 index = 0; index < enemy_num-1; index++)
		{
			Enemy_Infos.Add(enemy_asset->Data[FMath::RandRange(0, ENEMY_NUM_MAX - 1)]); // ランダムスポーン
		}
	}
}

void UBattle_Command_Widget::Pressed_kougeki()
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound_Select);
	enemy_canvas->SetVisibility(ESlateVisibility::Visible);
	for (int32 index = 0; index < enemy_num; ++index)
	{
		enemy_buttons[index]->SetVisibility(ESlateVisibility::Visible);
		enemy_texts[index]->SetVisibility(ESlateVisibility::Visible);
		enemy_num_texts[index]->SetVisibility(ESlateVisibility::Visible);
	}

	disable_spacer->SetVisibility(ESlateVisibility::Visible);
	setkougekiButton(false);
	party_canvas->SetRenderOpacity(0.4f);
}

bool UBattle_Command_Widget::is_Spacer_Visible()
{
	if (disable_spacer->GetVisibility() == ESlateVisibility::Visible)
		return true;
	else
		return false;
}

void UBattle_Command_Widget::backCommand()
{
	disable_spacer->SetVisibility(ESlateVisibility::Hidden);
	enemy_canvas->SetVisibility(ESlateVisibility::Hidden);
	party_canvas->SetRenderOpacity(1.0f);
}

void UBattle_Command_Widget::SpawnEnemy()
{
	FVector pos = FVector(600, 0, 20);
	FVector prev = pos;
	FRotator rotate = FRotator(0, -180, 0);
	int32 count = 1;

	if (enemy_num % 2 != 0) // 敵の数が奇数の時
	{
		int32 ratio = 0;

		if (1 < enemy_num)
			ratio = MAX_POS_R / ((enemy_num - 1) / 2);

		for (int32 index = 0; index < enemy_num; ++index)
		{
			FString str = Enemy_Infos[index].NAME.ToString() + "_BP";
			FString name = str + "." + str + "_C'";
			FString path = "/Script/Engine.Blueprint'/Game/DragonQuest8_like/Scenes/Battle/Enemy/" + name;
			TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); // 上記で設定したパスに該当するクラスを取得
			if (sc != nullptr)
			{
				AActor* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理
				FVector p;
				if (index % 2 != 0) // 右側に配置
				{
					p = pos + FVector(0, ratio * count, 0);
					prev = p;
					count++;
				}
				else // 左側に配置
				{
					p = FVector(prev.X, -prev.Y, prev.Z);
				}
				//UKismetSystemLibrary::PrintString(this, "(" + FString::FromInt(p.X) + ", " + FString::FromInt(p.Y) + ", " + FString::FromInt(p.Z) + ")", true, true, FColor::Cyan, 10.f, TEXT("None"));
				a->SetActorLocation(p);
				a->SetActorRotation(rotate);
			}

		}
	}
	else // 敵の数が偶数の時
	{
		int32 ratio = MAX_POS_R / enemy_num;
		for (int32 index = 0; index < enemy_num; ++index)
		{
			FString str = enemy_texts[index]->GetText().ToString() + "_BP";
			FString name = str + "." + str + "_C'";
			FString path = "/Script/Engine.Blueprint'/Game/DragonQuest8_like/Scenes/Battle/Enemy/" + name;
			TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); // 上記で設定したパスに該当するクラスを取得
			if (sc != nullptr)
			{
				AActor* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理
				FVector p;

				if (index % 2 != 0) // 左側に配置
				{
					p = FVector(prev.X, -prev.Y, prev.Z);
				}
				else // 右側に配置
				{
					p = prev + FVector(0, ratio * count, 0);
					prev = p;
					count++;
				}

				a->SetActorLocation(p);
				a->SetActorRotation(rotate);
			}

		}

	}

}

void UBattle_Command_Widget::decrease_enemy_hp(int32 hp)
{
	UKismetSystemLibrary::PrintString(this, "before: " + FString::FromInt(Enemy_Infos[0].HP), true, true, FColor::Cyan, 50.f, TEXT("None"));
	Enemy_Infos[0].HP -= hp;
	UKismetSystemLibrary::PrintString(this, "after: " + FString::FromInt(Enemy_Infos[0].HP), true, true, FColor::Cyan, 50.f, TEXT("None"));
}

void UBattle_Command_Widget::setkougekiButton(bool b)
{
	kougeki_button->SetIsEnabled(b);
}