// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryItem.h"

void ADeliveryItem::AssignIDAndColor(int _ID, FColor _Color, UMaterial* _Material)
{
	m_DestinationID = _ID;
	
	if (m_Mesh && _Material)
	{
		UMaterialInstanceDynamic* DynamicMaterialInst = UMaterialInstanceDynamic::Create(_Material, m_Mesh);
		m_Mesh->SetMaterial(0, DynamicMaterialInst);
	}
}

int ADeliveryItem::GetDestinationID()
{
	return m_DestinationID;
}