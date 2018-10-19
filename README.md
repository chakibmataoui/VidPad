# VidPad
The project VidPad is a suite of softwares for video mixing using keyboard mapping or midi input. 

I started this project in 2015 but the idea came way ago
I haven't progressed on this project since then.
I also didn't have time to check all what i have done back in 2015.
I was doing it on my free time for my first year in college.

Here is the small description of the project i wrote in 2016 as an updated idea :

VidPad project(v2)

 I-Introduction : 
	
	VidPad is a suite of softwares for live film making. The main goal of the software is to give users a complete toolset for programming their video live set and to play them live with keyboard or midi instruments.
	The idea came from making it for a stream live show on the internet, or a gig where there's a big LED screen in the background and the performer in the front controlling the videos.
	The software should be for both average user and expirimented users, and also programmers which like to dig into very deep details of softwares they use.
	
II-Liste of softwares : 
	This list will be détailed later in the document : 
	-VidPad Live : For live performance 
	-VidPad Flm : For midi editing
	-VidPad Edit : For creating and programming a project

III-Structure of a live set:
	There's one principale key-MIDI instrument which is used to control videos.
	Each video used in the set is defined in the loading of the project. Each video has 
	-Path :
		Path to the file that contains the video
	-Video informations :
		Informations about the video, the coding …
	-Markers : 	
		They will define a specific moment at the video, there are two default marker for each video {begin,end}

	Each key is assigned to a moment of a video or an interval and it has many proprities in addition to the instrumental tone and key:
	-Type of key : 
		Static (the video is played to its end) |
 		Looped (The video loops while the key is played) | 
		Momentum (The video plays to it's end while the key is played) | 
		Reversed (The video plays forward and backward while the key is played) | 
		JumpCut (Each time the key is played it plays a specific moment of the video) 
	-Sample :
		Each video has many key points defined by the creator. For a video there's at least two keys {begin,end} then the users defines others he wants to add in his project file for example : {begin,1:23:25,end} so a key is assigned not only to a key but to two keys one to define the beginning of the video and the other one to define the ending of the video so it can loops for example.
	-Audio :
		Each Key have a value that tels it if to play the audio of the video or not
	-Effect :
		There will be plugins to be added as effects for a video so the key could play them. For example : scaling , mirror , rotation , color effects and distortion ...
