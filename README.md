# True First Person System (Unreal Engine)

This is a modular **True First Person** system for Unreal Engine, focused on full-body awareness, smooth camera integration, and responsive character control. The system is under active development and will continue to evolve with new features and engine updates.

🔗 **Design Blog & Documentation**  
You can find the full technical breakdown, design motivation, and implementation guide here:  
👉 [View the Design Page](https://www.notion.so/True-First-Person-Perspective-Unreal-Engine-5-1de2cb6e5e868052b68bdc83fffbc4be?pvs=4)

---

## ⚠️ Disclaimer

This repository contains only **C++ source code** — it does **not include animations, Control Rigs, or any Unreal asset files (uassets)**.

If you're following the instructions in the design blog, **you don't need to download this plugin**. The guide provides everything needed to recreate the system using your own assets and setup.

---

## 🛠️ Features (Current)

- First-person camera physically attached to the character's head socket
- Full-body visibility in first person
- Custom character movement system with support for stances and speeds
- Stabilized animation using Control Rig and Aim Offset (manual setup required)
- Clean separation of logic for future extensibility

---

## 🚧 Development Plans

- Upgrade to **MoverComponent** once it becomes stable in future Unreal versions
- Expand support for procedural animation and combat stances
- Create a reusable plugin version with sample assets and rig presets

---

## 💡 Notes

- Some classes are currently empty or minimal — these are reserved for future expansion.
- For a basic implementation, **everything you need is already inside the character class**.
- If you do decide to download this code, you’ll still need to create:
  - Your own Control Rigs (for head/spine stabilization)
  - Aim Offset poses
  - Animation Blueprint and State Machine

This repository is shared as a technical reference for learning and experimentation — not as a drop-in gameplay system.

---

Thanks for checking it out!
