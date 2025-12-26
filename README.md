# Project_GAS_CC

Developed with Unreal Engine 5.7.1  

Part 1 https://github.com/Mahdi94x/Project_GAS_CC  

Based on the Udemy course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri  

Project GAS_CC is a third-person action combat prototype built in Unreal Engine using the Gameplay Ability System (GAS).  
The project was created as a hands-on deep dive into GAS, implementing all gameplay mechanics—player abilities, AI behavior, combat logic, attributes, and UI—using GAS-driven architecture.  
The project combines C++ and Blueprints to demonstrate scalable, multiplayer-ready gameplay systems with clean separation between logic, effects, and visuals.  

Core Features  

Gameplay Ability System (GAS) Architecture

* Custom Ability System Component with extended functionality
* Attribute Sets for Health, Mana
* Gameplay Effects for attribute modification, initialization, Respawning, status effects, costs, and cooldowns
* Gameplay Tags created and managed both in-editor and in C++
* All gameplay mechanics implemented using GAS principles

Player Input & Control  

* Enhanced Input system setup
* Separate Input Mapping Contexts for movement and abilities
* Ability activation driven through GAS rather than direct input logic
* Clean Player Controller–based input handling

Combat & Abilities  

* Multiple combat abilities implemented as Gameplay Abilities
* Directional hit reactions driven by ability logic
* Ability-based hit detection using overlap tests and collision filtering
* Ability costs and cooldowns fully managed through Gameplay Effects
* Character death and respawn handled via GAS state and tags

AI Systems  

* Enemy AI built entirely using Gameplay Abilities
* AI searching, chasing, and attacking behaviors
* AI abilities share the same GAS framework as the player
* Scalable structure for adding new enemy types and behaviors

Gameplay Cues & Visual Feedback (For Player Character)  

* Gameplay Cues for playing animation montages
* Particle effects triggered through GAS
* Camera shakes for impactful combat feedback
* Niagara-based GPU damage numbers for real-time combat feedback

Ability Tasks & Custom C++ Extensions  

* Use of built-in Ability Tasks for async ability logic
* Custom Ability Tasks written in C++
* Custom Latent Task nodes to extend Blueprint functionality
* Event-driven abilities responding to Gameplay Events

UI & Attribute Feedback  

* UI widgets responding to Attribute change delegates
* Health and Mana bars updated in real time
* Floating damage numbers driven by attribute changes
* Clean separation between gameplay logic and UI presentation

Pickups & World Interaction  

* Health and Mana pickups implemented via Gameplay Effects
* Attribute modification and tag application on pickup
* Modular pickup system for easy expansion

Animation & Combat Polish  

* Animation Montages triggered via Gameplay Cues for player and Gameplay ability for enemies
* Custom Anim Notifies and Notify States
* Clean synchronization between animation, damage, and effects
* Optimized collision and overlap handling for performance

Tools & Technologies  

* Unreal Engine 5
* C++ and Blueprints
* Gameplay Ability System (GAS)
* Enhanced Input System
* Niagara VFX
* Epic Games Paragon Assets (Minions and Boras)

Learning Focus  

* Deep understanding of Unreal Engine’s Gameplay Ability System
* Designing scalable, multiplayer-friendly gameplay systems
* Hybrid C++ / Blueprint workflows
* Event-driven gameplay architecture
* Clean code organization for complex combat systems
