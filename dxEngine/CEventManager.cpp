#include "CEventManager.h"

unsigned __stdcall ClientReceiveThread(VOID* c)
{
	CEventManager* ec = (CEventManager*)c;
#ifdef _DEBUG
	ec->globalObjects->errorLog->WriteError("ClientReceiveThread Starting\n");
#endif
	while (ec->isRunning)
	{
		if (ec->client)
		{
			if (ec->client->connectionState == CClient::CS_NOTCONNECTED)
			{
				ec->isRunning = FALSE;
			}
			else
			{
				ec->client->ClientReceive();

				if (ec->client->packet->type)
				{
					ec->ProcessEvent(ec->client->packet);
				}
			}
		}
	}
#ifdef _DEBUG
	ec->globalObjects->errorLog->WriteError("ClientReceiveThread Ending\n");
#endif
	_endthreadex(0);

	return 0;
}

CEventManager::CEventManager()
{
	memset(this, 0x00, sizeof(CEventManager));
}

CEventManager::CEventManager(CGlobalObjects* g, CColor* cc)
{
	memset(this, 0x00, sizeof(CEventManager));

	globalObjects = g;

	clearColor = cc;

	chatText = new CString(128);
	debugText = new CString(128);
	//console = new CConsole(globalObjects, "console.jpg", "CalibriBold");
	console = new CConsole(globalObjects, "console.jpg", "Calibri");
	midiSong = new CMidi(globalObjects, "flourish.mid");

	CVertex2 v1(104.0F, 28.0F);
	CVertex2 v2(100.0F, 300.0F);
	buttonExit = new CButton(globalObjects, "exit.png", "exitO.png", &v1, &v2, CPacket::PT_LOCAL, CPacket::PT_EXIT);

	//middle = new CHudImage(globalObjects, "middle.tga", &CVertex2(32.0F, 32.0F), &CVertex2((FLOAT)globalObjects->window->width / 2, (FLOAT)globalObjects->window->height / 2), NULL);
	//spinnyThing = new CHudImage(globalObjects, "front.png", &CVertex2(64.0F, 64.0F), &CVertex2((FLOAT)globalObjects->window->width / 2, 32.0F), NULL);

	CVertex v(95.0F, 4.0F, 0.0F);

	pointLight = new CPointLight(0, &v, &LovelyPurple, 32.0F, 0.50f, 0.0001250f, 8.0F);
	
	weaponReload = new CTimer(50);

	//spinnyThing->rotZ = 180.0F;

	if (globalObjects->effectMgr->effects)
	{
		CLinkListNode* el = globalObjects->effectMgr->effects->list;

		while (el->element)
		{
			CEffect* eff = (CEffect*)el->element;

			if (eff->hlightAmbient)
			{
				hr = eff->effect->SetFloat(eff->hlightAmbient, console->variables->timeOfDay);
			}

			if (eff->hfogColor)
			{
				hr = eff->effect->SetFloatArray(eff->hfogColor, LightGray.GetFloatArray(), 4);

				hr = eff->effect->SetFloat(eff->hfogStart, 2.0F);
				hr = eff->effect->SetFloat(eff->hfogEnd, 1024.0F);
				hr = eff->effect->SetFloat(eff->hminFog, 0.0F);
				hr = eff->effect->SetFloat(eff->hmaxFog, 1.0F);
			}

			if (eff->hlightCount)
			{
				hr = eff->effect->SetInt(eff->hlightCount, 1);

				hr = eff->effect->SetFloatArray(eff->hlightPosition, (FLOAT*)& pointLight->position, CPointLight::MAXLIGHTS * 4);
				hr = eff->effect->SetFloatArray(eff->hlightColor, (FLOAT*)& pointLight->color, CPointLight::MAXLIGHTS * 4);
				hr = eff->effect->SetFloatArray(eff->hlightRadius, (FLOAT*)& pointLight->radius, CPointLight::MAXLIGHTS);
				hr = eff->effect->SetFloatArray(eff->hlightLinear, (FLOAT*)& pointLight->linear, CPointLight::MAXLIGHTS);
				hr = eff->effect->SetFloatArray(eff->hlightQuadratic, (FLOAT*)& pointLight->quadratic, CPointLight::MAXLIGHTS);
				hr = eff->effect->SetFloatArray(eff->hlightIntensity, (FLOAT*)& pointLight->intensity, CPointLight::MAXLIGHTS);
			}

			el = el->next;
		}
	}

	projectiles = new CLinkList();
}

CEventManager::~CEventManager()
{
	delete chatText;
	delete debugText;
	delete console;
	delete midiSong;
	delete buttonExit;
	//delete middle;
	//delete spinnyThing;
	delete weaponReload;
	delete pointLight;
	delete projectiles;
	delete client;
	delete brushMap;
	delete players;
	delete terrain;
	delete currentCamera;
	delete billboard;
	delete namePlate;
	delete orthoLevel;
	delete orthoPlayers;
	delete server;
}

VOID CEventManager::SendEvent(CPacket* p)
{
	if ((client == NULL) || (p->audience == CPacket::PT_LOCAL))
	{
		CEventManager::ProcessEvent(p);

		return;
	}

	client->SendEvent(p);
}

VOID CEventManager::ProcessEvent(CPacket* p)
{
	switch (p->type)
	{
		case CPacket::PT_FRAME:
		{
			CEventManager::Frame(p);

			break;
		}

		case CPacket::PT_EXIT:
		{
			CEventManager::Exit(p);

			break;
		}

		case CPacket::PT_PONG:
		{
			globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:PONG\n");

			SIZE_T startTime;
			memcpy(&startTime, p->data, p->length);

			SIZE_T currTime = (SIZE_T)GetTickCount64();

			pingRate = currTime - startTime;

			console->AddEventMessage("Pong %I64d %I64d", currTime, pingRate);

			break;
		}

		case CPacket::PT_ATTACK:
		{
			if (weaponReload->isReloading)
			{
				break;
			}

			weaponReload->Start();

			//globalObjects->soundMgr->GetSound("shotgun.wav")->StartSound();

			if (players)
			{
				CLinkListNode* lln = players->Search(p->fromClient);

				if (lln)
				{
					CPlayer* pplayer = (CPlayer*)lln->element;

					CVertex t = pplayer->position + (pplayer->camera->look * 128.0F);

					CVertex v1(4.0F, 4.0F, 4.0F);

					CVertex2 v2(1.0F, 1.0F);

					CVertex2 v3(0.0F, 0.0F);

					CDBrush* tb = new CDBrush(globalObjects, &t, &v1, &v2, &v3, rand() % 20000);

					for (UINT i = 0; i < 6; i++)
					{
						tb->side[i]->texture = globalObjects->textureMgr->GetTexture("blue.png");
						tb->side[i]->effect = globalObjects->effectMgr->GetEffect("brush.fx");
					}

					tb->timer->Start();

					tb->rotation.X = pplayer->camera->rotation.X;
					tb->rotation.Y = pplayer->camera->rotation.Y;
					tb->rotation.Z = pplayer->camera->rotation.Z;

					tb->direction = pplayer->camera->look;

					tb->xmfspin.x = pplayer->camera->look.X;
					tb->xmfspin.y = pplayer->camera->look.Y;
					tb->xmfspin.z = pplayer->camera->look.Z;

					tb->rotA = 90.0F;

					projectiles->Add(tb, NULL);
				}
			}

			break;
		}

		case CPacket::PT_CONSOLEPAGING:
		{
			console->Paging((CHAR)* p->data);

			break;
		}

		case CPacket::PT_CONSOLEINPUT:
		{
			CEventManager::ConsoleInput(p);

			break;
		}

		case CPacket::PT_TOGGLECONSOLE:
		{
			if (consoleVisible)
			{
				consoleVisible = FALSE;
			}
			else
			{
				consoleVisible = TRUE;
			}

			break;
		}

		case CPacket::PT_LOADTERRAIN:
		{
			CEventManager::LoadTerrain(p);

			break;
		}

		case CPacket::PT_LOADBRUSHMAP:
		{
			CEventManager::LoadBrushMap(p);

			break;
		}

		case CPacket::PT_LOADORTHOLEVEL:
		{
			CEventManager::LoadOrthoLevel(p);

			break;
		}

		case CPacket::PT_STARTSERVER:
		{
			CEventManager::StartServer();

			break;
		}

		case CPacket::PT_STOPSERVER:
		{
			if (!server)
			{
				globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Server Not Running\n");

				break;
			}

			globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Stopping Server\n");

			server->Shutdown();

			break;
		}

		case CPacket::PT_CONNECT:
		{
			CEventManager::ClientConnect(p);

			break;
		}

		case CPacket::PT_DISCONNECT:
		{
			if (client)
			{
				if (client->connectionState != CClient::CS_CONNECTED)
				{
					globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Not Connected\n");

					break;
				}
			}
			else
			{
				break;
			}

			globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Disconnect:%i\n", p->fromClient);

			isRunning = FALSE;

			rv = WaitForSingleObjectEx(hThread, 2000, FALSE);

			CloseHandle(hThread);

			client->Disconnect();

			CPacket* packet = new CPacket(p->fromClient, p->toClient, CPacket::PT_LOCAL, CPacket::PT_ORTHOPLAYEREXIT, CPacket::PT_EMPTY, 1);

			CEventManager::SendEvent(packet);

			delete packet;


			packet = new CPacket(p->fromClient, p->toClient, CPacket::PT_LOCAL, CPacket::PT_PLAYEREXIT, CPacket::PT_EMPTY, 1);

			CEventManager::SendEvent(packet);

			delete packet;

			break;
		}

		case CPacket::PT_ACCEPTED:
		{
			globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Accepted:%i\n", p->fromClient);

			client->clientNbr = p->toClient;

			client->connectionState = CClient::CS_CONNECTED;

			break;
		}

		case CPacket::PT_WINDOWMODE:
		{
			globalObjects->videoDevice->ToggleWindowMode();

			break;
		}

		case CPacket::PT_ORTHOPLAYERENTER:
		{
			CEventManager::OrthoPlayerEnter(p);

			break;
		}

		case CPacket::PT_ORTHOPLAYEREXIT:
		{
			CEventManager::OrthoPlayerExit(p);

			break;
		}

		case CPacket::PT_PLAYERENTER:
		{
			CEventManager::PlayerEnter(p, 128.0F);

			break;
		}

		case CPacket::PT_PLAYEREXIT:
		{
			CEventManager::PlayerExit(p);

			break;
		}

		case CPacket::PT_CHAT:
		{
			chatText->Clear();

			sprintf_s(chatText->GetText(), 80, "%i %s", p->fromClient, p->data);

			globalObjects->errorLog->WriteError("%s\n", chatText->GetText());

			console->AddEventMessage(chatText->GetText());

			break;
		}

		case CPacket::PT_MOVE_UP:
		case CPacket::PT_MOVE_LEFT:
		case CPacket::PT_MOVE_RIGHT:
		case CPacket::PT_MOVE_DOWN:
		{
			if (orthoPlayers)
			{
				CLinkListNode* lln = orthoPlayers->Search(p->fromClient);

				if (lln)
				{
					COrthoPlayer* op = (COrthoPlayer*)lln->element;

					op->PlayerMove(p);
				}
			}

			if (p->type == CPacket::PT_MOVE_UP)
			{
				console->variables->timeOfDay += globalObjects->frametime->frametime;
			}

			if (p->type == CPacket::PT_MOVE_DOWN)
			{
				console->variables->timeOfDay -= globalObjects->frametime->frametime;
			}


			break;
		}

		case CPacket::PT_FORWARD:
		case CPacket::PT_BACKWARD:
		case CPacket::PT_STRAFELEFT:
		case CPacket::PT_STRAFERIGHT:
		{
			if (players)
			{
				CLinkListNode* lln = players->Search(p->fromClient);

				if (lln)
				{
					CPlayer* pla = (CPlayer*)lln->element;

					pla->PlayerMove(p);
				}
			}

			break;
		}
	}
}

VOID CEventManager::CommandFromConsole()
{
	if (strcmp(console->commandLine->GetText(), "/exit") == 0)
	{
		CPacket* packet = new CPacket(0, 0, CPacket::PT_LOCAL, CPacket::PT_EXIT, CPacket::PT_EXIT, 1);

		CEventManager::SendEvent(packet);

		delete packet;

		return;
	}

	if (strcmp(console->commandLine->GetText(), "/ping") == 0)
	{
		if (client == NULL)
		{
			return;
		}

		SIZE_T startTime = (SIZE_T)GetTickCount64();

		console->AddEventMessage("Ping %I64d", startTime);

		CPacket* packet = new CPacket(client->clientNbr, client->clientNbr, CPacket::PT_SINGLE, CPacket::PT_PING, (BYTE*)& startTime, sizeof(SIZE_T));

		CEventManager::SendEvent(packet);

		delete packet;

		return;
	}

	if (strcmp(console->commandLine->GetText(), "/wire") == 0)
	{
		if (console->variables->drawWire)
		{
			console->variables->drawWire = FALSE;
		}
		else
		{
			console->variables->drawWire = TRUE;
		}

		console->AddEventMessage("drawWire %x", console->variables->drawWire);

		return;
	}

	UINT i = 0;

	CHAR c[32] = {};

	while ((console->commandLine->GetText()[i] != ' ') && (console->commandLine->GetText()[i] != '\0'))
	{
		memcpy(&c[i], &console->commandLine->GetText()[i], 1);

		i++;
	}

	i++;

	UINT ii = 0;

	CHAR v[32] = {};

	while (console->commandLine->GetText()[i] != '\0')
	{
		memcpy(&v[ii], &console->commandLine->GetText()[i], 1);

		ii++;
		i++;
	}

	if (strcmp(c, "/fog") == 0)
	{
		console->variables->fog = (FLOAT)atof(v);

		console->AddEventMessage("fog %f", console->variables->fog);

		return;
	}

	if (strcmp(c, "/tod") == 0)
	{
		console->variables->timeOfDay = (FLOAT)atof(v);

		console->AddEventMessage("timeOfDay %f", console->variables->timeOfDay);

		return;
	}

	if (strcmp(c, "/connect") == 0)
	{
		CPacket* packet = new CPacket(0, 0, CPacket::PT_LOCAL, CPacket::PT_CONNECT, v, (UINT)strlen(v));

		CEventManager::SendEvent(packet);

		delete packet;

		return;
	}

	if (strcmp(c, "/disconnect") == 0)
	{
		CPacket* packet = new CPacket(0, 0, CPacket::PT_LOCAL, CPacket::PT_DISCONNECT);

		CEventManager::SendEvent(packet);

		delete packet;

		return;
	}

	console->AddEventMessage("Unknown Command:%s", c);
}

VOID CEventManager::ClientConnect(CPacket* p)
{
	if (client)
	{
		if (client->connectionState == CClient::CS_CONNECTED)
		{
			globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Already Connected:%i\n", p->fromClient);

			return;
		}

		delete client;
	}

	globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Connect\n");

	client = new CClient(globalObjects, p);

	isRunning = TRUE;

	hThread = (HANDLE)_beginthreadex(NULL, 0, &ClientReceiveThread, (VOID*)this, 0, &receiveThreadId);
}

VOID CEventManager::ConsoleInput(CPacket* p)
{
	if (p->data[0] == VK_RETURN)
	{
		if (console->commandLine->GetText()[0] != '/')
		{
			CEventManager::SendGlobalChat();

			console->Reset();

			return;
		}
		else
		{
			CEventManager::CommandFromConsole();

			console->Reset();

			return;
		}
	}

	console->AddCHAR((CHAR)* p->data);
}

VOID CEventManager::Draw2D(CPacket* p)
{
	if (orthoLevel)
	{
		orthoLevel->Draw();
	}

	if (orthoPlayers)
	{
		CLinkListNode* opl = orthoPlayers->list;

		while (opl->element)
		{
			if (opl->deleteMe)
			{
				opl = orthoPlayers->Delete(opl);
			}
			else
			{
				COrthoPlayer* op = (COrthoPlayer*)opl->element;

				op->sprite->Draw();

				opl = opl->next;
			}
		}
	}

	if (brushMap || terrain)
	{
		//middle->Draw();
	}

	if (buttonExit)
	{
		buttonExit->Draw();

		if ((buttonExit->isMouseOver) && (globalObjects->mouse->keyMap[CMouseDevice::LMB]->count == 1))
		{
			CEventManager::SendEvent(buttonExit->packet);
		}
	}

	//spinnyThing->UpdateRotation();
	//spinnyThing->Draw();
}

VOID CEventManager::Draw3D(CPacket* p)
{
#ifdef _DEBUG
	if (console->variables->drawWire)
	{
		hr = globalObjects->videoDevice->device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		hr = globalObjects->videoDevice->device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif

	CPlayer* pplayer = 0;

	if (players)
	{
		CLinkListNode* pl = players->list;

		while (pl->element)
		{
			if (pl->deleteMe)
			{
				pl = players->Delete(pl);
			}
			else
			{
				CPlayer* pla = (CPlayer*)pl->element;

				pla->camera->UpdateRotation((globalObjects->mouse->state.lY * globalObjects->mouse->sensitivity), (globalObjects->mouse->state.lX * globalObjects->mouse->sensitivity), (globalObjects->mouse->state.lZ * globalObjects->mouse->sensitivity));

				pla->camera->UpdateView();

				currentCamera->Copy(pla->camera);

				if (sound3D)
				{
					sound3D->SetListener(&pla->camera->position, &pla->camera->look, &pla->camera->up);
				}

				pplayer = pla;

				pl = pl->next;
			}
		}
	}

	if (namePlate)
	{
		namePlate->billboard->position.X -= 4 * globalObjects->frametime->frametime;
		pointLight->position[0][0] -= 4 * globalObjects->frametime->frametime;
	}

	if (globalObjects->effectMgr->effects)
	{
		CLinkListNode* el = globalObjects->effectMgr->effects->list;

		while (el->element)
		{
			CEffect* eff = (CEffect*)el->element;

			if (currentCamera)
			{
				wvp = globalObjects->videoDevice->worldMatrix * currentCamera->view * globalObjects->videoDevice->projMatrix;

				hr = eff->effect->SetMatrix(eff->hview, &currentCamera->view);

				hr = eff->effect->SetMatrix(eff->hwvp, &wvp);
			}

			if (eff->hlightAmbient)
			{
				hr = eff->effect->SetFloat(eff->hlightAmbient, console->variables->timeOfDay);
			}

			if (eff->hfogDensity)
			{
				hr = eff->effect->SetFloat(eff->hfogDensity, console->variables->fog);
			}

			if (brushMap)
			{
				if (pplayer)
				{
					pointLight->position[0][0] = pplayer->position.X;
					pointLight->position[0][1] = pplayer->position.Y;
					pointLight->position[0][2] = pplayer->position.Z;
				}
			}

			if (eff->hlightPosition)
			{
				hr = eff->effect->SetFloatArray(eff->hlightPosition, (FLOAT*)& pointLight->position, CPointLight::MAXLIGHTS * 4);
				hr = eff->effect->SetFloatArray(eff->hlightColor, (FLOAT*)& pointLight->color, CPointLight::MAXLIGHTS * 4);
			}

			el = el->next;
		}
	}

	if (terrain)
	{
		terrain->Draw();
	}

	if (brushMap)
	{
		brushMap->Draw();
	}

	if (projectiles)
	{
		CLinkListNode* pl = projectiles->list;

		while (pl->element)
		{
			if (pl->deleteMe)
			{
				pl = projectiles->Delete(pl);
			}
			else
			{
				CDBrush* bru = (CDBrush*)pl->element;

				bru->timer->Frame();

				if (bru->timer->isReloading)
				{
					bru->position += bru->direction * (64.0F * globalObjects->frametime->frametime);

					bru->rotA += (90.0F * globalObjects->frametime->frametime);

					bru->Rotation();

					bru->Draw();
				}
				else
				{
					pl->deleteMe = TRUE;
				}

				pl = pl->next;
			}
		}
	}
#ifdef _DEBUG
	if (pplayer)
	{
		pplayer->DrawDebug();
	}
#endif
	if (currentCamera)
	{
		if (billboard)
		{
			billboard->SetView(currentCamera->view);

			billboard->Draw();
		}

		if (namePlate)
		{
			namePlate->billboard->SetView(currentCamera->view);

			namePlate->Draw();
		}
	}
}

VOID CEventManager::Frame(CPacket* p)
{
	if (weaponReload)
	{
		weaponReload->Frame();
	}

	hr = globalObjects->videoDevice->device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(clearColor->r, clearColor->g, clearColor->b), 1.0F, 0);
	hr = globalObjects->videoDevice->device->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(clearColor->r, clearColor->g, clearColor->b), 1.0F, 0);

	hr = globalObjects->videoDevice->device->BeginScene();

	CEventManager::Draw3D(p);

	CEventManager::Draw2D(p);

	CEventManager::DrawDXText(p);

	if (consoleVisible)
	{
		console->DisplayConsole();
	}

	hr = globalObjects->videoDevice->device->EndScene();

	hr = globalObjects->videoDevice->device->Present(NULL, NULL, NULL, NULL);
}

VOID CEventManager::DrawDXText(CPacket* p)
{
	debugText->Format(" FPS: %i %0.6f", globalObjects->frametime->rframeCount, globalObjects->frametime->rframetime);
	globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 10, &White);


#ifdef _DEBUG
	if (client)
	{
		if (client->connectionState == CClient::CS_CONNECTED)
		{
			debugText->Format("Ping: %I64d", pingRate);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 136, 10, &White);
		}
	}

	if (weaponReload)
	{
		debugText->Format("Fire: %d", weaponReload->isReloading);
		globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 22, &White);

		if (projectiles)
		{
			debugText->Format("Proj: %d", projectiles->count);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 74, 22, &White);
		}
	}

	if (players)
	{
		CLinkListNode* lln = players->Search(p->fromClient);

		if (lln)
		{
			CPlayer* pla = (CPlayer*)lln->element;

			debugText->Format(" Pos: %f %f %f %i %i", pla->camera->position.X, pla->camera->position.Y, pla->camera->position.Z, pla->x, pla->z);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 34, &White);

			debugText->Format(" Rot: %f %f %f", pla->camera->rotation.X, pla->camera->rotation.Y, pla->camera->rotation.Z);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 46, &White);

			debugText->Format("CDir: %f %f %f", pla->camera->look.X, pla->camera->look.Y, pla->camera->look.Z);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 58, &White);

			debugText->Format("TDir: %f %f %f", pla->direction.X, pla->direction.Y, pla->direction.Z);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 70, &White);

			debugText->Format("Clip: u:%f v:%f l:%f", pla->collision->u, pla->collision->v, pla->collision->l);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 82, &White);

			debugText->Format(" Pop: %f %f %f", pla->pop.X, pla->pop.Y, pla->pop.Z);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 94, &White);

			if (pla->tc)
			{
				debugText->Format(" sp1: %d sp2:%d", pla->tc->sp1, pla->tc->sp2);
				globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 106, &White);
			}
		}
	}

	if (orthoPlayers)
	{
		CLinkListNode* lln = orthoPlayers->Search(p->fromClient);

		if (lln)
		{
			COrthoPlayer* op = (COrthoPlayer*)lln->element;

			debugText->Format(" TDir: %f %f", op->direction.X, op->direction.Y);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 34, &White);

			debugText->Format(" Pos: %f %f", op->position.X, op->position.Y);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 46, &White);

			debugText->Format("Coord: %f %f", op->coordinates.X, op->coordinates.Y);
			globalObjects->fontDXMgr->GetFont("Calibri")->Draw(debugText->GetText(), 10, 58, &White);
		}
	}
#endif
}

VOID CEventManager::Exit(CPacket* p)
{
	isExiting = TRUE;

	globalObjects->errorLog->WriteError("CEventManager::Exit:Exiting\n");

	if (client)
	{
		if (client->connectionState == CClient::CS_CONNECTED)
		{
			isRunning = FALSE;

			rv = WaitForSingleObjectEx(hThread, 2000, FALSE);

			CloseHandle(hThread);

			client->Disconnect();
		}
	}

	if (server)
	{
		if (server->acceptRunning)
		{
			server->Shutdown();
		}
	}

	PostMessage(globalObjects->window->hWnd, WM_DESTROY, NULL, NULL);
}

VOID CEventManager::LoadBrushMap(CPacket* p)
{
	if (brushMap)
	{
		delete brushMap;
		brushMap = 0;

		delete currentCamera;
		currentCamera = 0;

		if (players)
		{
			delete players;
			players = 0;
		}

		return;
	}

	brushMap = new CBrushMap(globalObjects, "map.txt");

	players = new CLinkList();

	currentCamera = new CCamera();

	CEventManager::PlayerEnter(p, 512.0F);
}

VOID CEventManager::LoadTerrain(CPacket* p)
{
	if (terrain)
	{
		delete terrain;
		terrain = 0;

		delete billboard;
		billboard = 0;

		delete namePlate;
		namePlate = 0;

		delete sound3D;
		sound3D = 0;

		delete currentCamera;
		currentCamera = 0;

		if (players)
		{
			delete players;
			players = 0;
		}

		return;
	}

	globalObjects->errorLog->WriteError("CEventManager::LoadTerrain\n");

	CVertex2 v1(2.0F, 1.0F);
	
	CVertex v2(100.0F, 8.0F, 0.0F);

	billboard = new CBillboard(globalObjects, "billboard.png", &v1, &v2, CBillboard::BT_DRAW);

	CVertex v3(95.0F, 8.0F, 0.0F);

	namePlate = new CNamePlate(globalObjects, "Verdana", "PlayerName", &Beer, &v3);

	CVertex v4(0.0F, 38.0F, 0.0F);
		
	sound3D = new CSound3D(globalObjects, "heli.wav", TRUE, &v4, 64.0F);

	terrain = new CTerrain(globalObjects, "vertices.txt");

	CVertex v5(95.0F, 4.0F, 0.0F);

	pointLight->SetLight(0, &v5, &LovelyPurple, 32.0F, 0.50f, 0.0001250F, 8.0F);

	players = new CLinkList();

	currentCamera = new CCamera();

	CEventManager::PlayerEnter(p, 1024.0F);

	CLinkListNode* lln = players->Search(p->fromClient);

	if (lln)
	{
		CPlayer* pla = (CPlayer*)lln->element;

		pla->position = CVertex(0.0F, 0.0F, 0.0F);

		//pla->position.Y = 3000.0F;
		//pla->position.X = -16384.0F;
		//pla->position.Z = -16384.0F;
		pla->position.Y = 38.0F;
		//pla->position.Y = 30000.0F;
		//pla->position.Y = 0.0F;

		pla->camera->position = pla->position;
	}

}

VOID CEventManager::LoadOrthoLevel(CPacket* p)
{
	if (orthoLevel)
	{
		if (orthoPlayers)
		{
			delete orthoPlayers;
			orthoPlayers = 0;
		}

		delete orthoLevel;
		orthoLevel = 0;

		return;
	}

	globalObjects->errorLog->WriteError("CEventManager::LoadOrthoLevel\n");

	CVertex2 v1(32.0F, 32.0F);

	CVertex2 v2(24.0F, 24.0F);

	orthoLevel = new COrthoLevel(globalObjects, "map.txt", &v1, &v2);

	orthoPlayers = new CLinkList();

	CEventManager::OrthoPlayerEnter(p);
}

VOID CEventManager::PlayerEnter(CPacket* p, FLOAT r)
{
	player = new CPlayer(globalObjects, brushMap, terrain, r, "PlayerName");

	globalObjects->errorLog->WriteError("CEventManager::PlayerEnter:Entered:%s\n", player->name->GetText());

	player->position = CVertex(-155.0F, -121.0F, 73.0F);

	player->camera->position = player->position;

	player->camera->rotation = CVertex(-90.0F, 48.0F, 0.0F);

	player->camera->UpdateRotation((globalObjects->mouse->state.lY * globalObjects->mouse->sensitivity), (globalObjects->mouse->state.lX * globalObjects->mouse->sensitivity), (globalObjects->mouse->state.lZ * globalObjects->mouse->sensitivity));
	player->camera->UpdateView();

	players->Add(player, p->fromClient);

	globalObjects->soundMgr->GetSound("chimes.wav")->StartSound();
}

VOID CEventManager::PlayerExit(CPacket* p)
{
	if (players)
	{
		CLinkListNode* lln = players->Search(p->fromClient);

		if (lln)
		{
			CPlayer* pla = (CPlayer*)lln->element;

			globalObjects->errorLog->WriteError("CEventManager::PlayerExit:Exited:%s\n", pla->name->GetText());

			lln->deleteMe = TRUE;
		}
	}
}

VOID CEventManager::OrthoPlayerEnter(CPacket* p)
{
	INT bs = rand() % orthoLevel->redStart->count;

	INT c = 0;

	CVertex2 start;

	CLinkListNode* lln = orthoLevel->redStart->list;

	while (lln->element)
	{
		COrthoTile* ot = (COrthoTile*)lln->element;

		if (c == bs)
		{
			start = CVertex2(ot->position.X, ot->position.Y);

			break;
		}

		c++;

		lln = lln->next;
	}

	CVertex2 v1(32.0F, 32.0F);

	CVertex2 v2(22.0F, 22.0F);

	orthoPlayer = new COrthoPlayer(globalObjects, orthoLevel, 256.0F, &v1, &v2, &start, "OrthoPlayerName");

	globalObjects->errorLog->WriteError("CEventManager::OrthoPlayerEnter:Entered:%s\n", orthoPlayer->name->GetText());

	orthoPlayers->Add(orthoPlayer, p->fromClient);

	globalObjects->soundMgr->GetSound("chimes.wav")->StartSound();

	//midiSong->PlayMidi();
}

VOID CEventManager::OrthoPlayerExit(CPacket* p)
{
	if (orthoPlayers)
	{
		CLinkListNode* lln = orthoPlayers->Search(p->fromClient);

		if (lln)
		{
			COrthoPlayer* op = (COrthoPlayer*)lln->element;

			globalObjects->errorLog->WriteError("CEventManager::OrthoPlayerExit:Exited:%s\n", op->name->GetText());

			lln->deleteMe = TRUE;
		}
	}
}

VOID CEventManager::SendGlobalChat()
{
	if (console->commandLine->GetLength() <= 0)
	{
		return;
	}

	UINT fc = 0;

	if (client)
	{
		fc = client->clientNbr;
	}

	CPacket* packet = new CPacket(fc, 0, CPacket::PT_GLOBAL, CPacket::PT_CHAT, console->commandLine->GetText(), console->commandLine->GetLength());

	CEventManager::SendEvent(packet);

	delete packet;
}

VOID CEventManager::StartServer()
{
	if (server)
	{
		if (server->acceptRunning)
		{
			globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Server Already Running\n");

			return;
		}

		delete server;
	}

	globalObjects->errorLog->WriteError("CEventManager::ProcessEvent:Starting Server\n");

	server = new CServer(globalObjects, "26105");
}