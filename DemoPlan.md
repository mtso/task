
Demo Plan

1. Start demo on a demo repo with existing .task data
2. Then demo how to initialize on a new repository?


Procedure

1. $ task
2. Lists all tasks by due date in chronological order (meaning the task that is due soonest is shown at the top)

> show all    

task a265bfa1c253019b96163a82a37c9d1c1332ac1a
Due: Mon Nov 24, 2016
	
	Implement BST Node

task 6f1dc4967f880dbc4d0b087c7b1367b5b07d4f81
Due: Mon Nov 25, 2016

  Implement BST Tree

task 252bc06763afb3b6c2a0802f7346700ab55f46f5
Due: Mon Nov 26, 2016

  Implement BST Node

3. Create a new task
> new "Write headers for hash table" due="3 days"

4. Show listing by filter

> show --filter="Implement BST Node"

task a265bfa1c253019b96163a82a37c9d1c1332ac1a
Due: Mon Nov 24, 2016
  
  Implement BST Node

task 252bc06763afb3b6c2a0802f7346700ab55f46f5
Due: Mon Nov 26, 2016

  Implement BST Node

5. Delete duplicate task
> delete 252b
Deleting task 252bc06763afb3b6c2a0802f7346700ab55f46f5

6. show command history
> history
delete 252bc06763afb3b6c2a0802f7346700ab55f46f5

5. Undo delete
> undo
Undo delete of 252bc06763afb3b6c2a0802f7346700ab55f46f5

6. show command history
> history




task log
delete [hash]
create [hash]
