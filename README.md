# CyrusGameDev
Unreal Engine Developer (C++)  Assignment (Junior)


Unreal FPS JSON Box Spawner Project
This project is a first-person shooter prototype built in Unreal Engine 5.6.0, where boxes are dynamically spawned based on a remote JSON file. Players can shoot and destroy the boxes to earn points.

 Features
🎯 FPS shooter gameplay using the First Person template

☁️ Remote JSON fetch (via native Unreal C++ HTTP module)

🧊 Box spawning based on JSON "types" and "objects" schema

🎨 Boxes colorized via dynamic materials from RGB values in JSON

💥 Damage + scoring system tied to player actions

📈 UI-ready score logic (can be exposed via UMG)


1. Remote JSON Fetch
UBoxDataFetcher uses FHttpModule to GET JSON from:
https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json
It parses the types[] and objects[] fields into structured FBoxTypeData and FBoxSpawnData.

2. Dynamic Box Spawning
UBoxSpawnerComponent spawns an AAColorBoxActor for each object using transform data.

Each box:

Is assigned a color using a dynamic material instance

Stores Health and Score from its type

3. GameMode Score Management
AFPSGameModeBase holds the current score.

Any box killed can call AddScore() to update it.

Easy to bind to a UI via UMG later.

4. Box Actor Behavior
Boxes reduce health when shot.

Destroyed when health reaches 0.

Triggers a score event.

🧪 How to Test
✅ Press Play in the editor

🎯 Move and shoot using WASD + mouse (standard FPS)

🧊 Boxes will spawn after JSON loads (check Output Log for confirmation)

🔫 Shoot a box — each hit deals 1 damage

💥 When health hits 0:

Box destroys itself

Score is updated (see log or extend with a UI)

