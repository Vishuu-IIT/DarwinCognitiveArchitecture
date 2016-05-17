# DarwinCognitiveArchitecture
This Repository contains all the modules of the Darwin Cognitive architecture implemented/tested on iCub humanoid, 
two cooperating indusrial robots perfoming assembly.

The Documentation section contains  two files 
1) Darwin Architecture (That describes the theoretical rationale of the framework, core subsystems
Observer or Central executive, Reasoning and Robot Episodic memory, PMP framework for Action Generation, Skill learning 
and Perceptual Modules

2) The User manual that descibes how to configure and use the various subssytems, either stand alone (for example, using the PMP framework
for action generation to control your robot) or as an Integrated architecture (Ex: Observer-Reasoning-Control loop) 
for some robot experiment etc....

The Src directory is subdivied into several subfolders mainly
Control: Has the PMP framework for action generation, motor skill learning, it contains 
a) Analytic solution that is implemented on iCub upperbody and Indsutrail assembly robots
b) Neural solution (that is trainable and custom configurable to control any robot: See user manual for further info

Reasoning: That has the Obsserver (The centrral executive) and Episodic memory (That holds cumulatively learnt expreinces, 
recalls them based on context and uses past experience to plan present behaviours)

GUI: Given the complexity of the architecture, various Visualization interfaces are developed to visualize activity
in all the core modules, to give the user an insider view

contact vishwanathan.mohan@iit.it or/ ajaz.bhat@iit.it for further info or assitance.
