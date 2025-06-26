# 🎮 CyrusGameDev

## 🛠 Unreal Engine Developer (C++) Assignment – Junior

---

# 🚀 Unreal FPS JSON Box Spawner Project

This project is a **first-person shooter prototype** built in **Unreal Engine 5.6.0**, where interactive boxes are dynamically spawned from a remote JSON file. Players can shoot and destroy the boxes to **earn points**.

---

## ✨ Features

- 🎯 FPS shooter gameplay using the **First Person template**
- ☁️ Remote **JSON fetch** using **native Unreal C++ HTTP module**
- 🧊 **Box spawning** driven by `types[]` and `objects[]` from JSON
- 🎨 **Dynamic material colors** using RGB values from JSON
- 💥 Simple **damage + scoring system** tied to player actions
- 📈 UI-ready score logic, easy to bind via UMG

---

## 📡 1. Remote JSON Fetch

- The `UBoxDataFetcher` component uses `FHttpModule` to **GET** data from:
https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json


- It parses:
- `types[]` → into `FBoxTypeData`
- `objects[]` → into `FBoxSpawnData`

---

## 🧱 2. Dynamic Box Spawning

- `UBoxSpawnerComponent` spawns `AAColorBoxActor` instances using transform data from the JSON.
- Each box:
- Has a **dynamic material** with its RGB color
- Stores **Health** and **Score** from its corresponding `type`

---

## 🎮 3. Game Mode Score Management

- `AFPSGameModeBase` tracks and updates the **player's score**
- Destroyed boxes call `AddScore()` to update the score
- Can be bound easily to **UI widgets (UMG)**

---

## 🔧 4. Box Actor Behavior

- Boxes reduce health when shot (1 damage per hit)
- On health reaching 0:
- The box is **destroyed**
- Score is **updated**
- Can trigger further UI or effects

---

## 🧪 How to Test

1. ✅ Press **Play** in the Unreal Editor
2. 🎯 Use **WASD** to move and **Mouse** to aim/shoot
3. 🧊 Boxes will spawn once JSON loads (check Output Log for success)
4. 🔫 Shoot a box — each hit deals 1 damage
5. 💥 When box health hits 0:
 - It **self-destructs**
 - Score is **updated** (check Output Log or integrate UMG)

---

## 📂 Key Classes & Responsibilities

| Class / Component      | Purpose                                      |
|------------------------|----------------------------------------------|
| `UBoxDataFetcher`      | Fetches and parses the remote JSON file      |
| `UBoxSpawnerComponent` | Spawns box actors using parsed JSON data     |
| `AAColorBoxActor`      | Represents individual, damageable colored boxes |
| `AFPSGameModeBase`     | Manages score and core gameplay logic        |

---

## ✅ Future Enhancements

- 🖼 Add score + health UI with **UMG**
- 🔊 Add **audio/visual effects** for hits and destruction
- 🌐 Make JSON URL configurable via project settings
- 💡 Add new box types or enemy behaviors

---

> 🧠 Built using **Unreal Engine 5.6.0**, native C++ only  
> 💻 No external plugins or blueprints used  
> 🎯 A focused technical test to showcase modular C++ gameplay systems
