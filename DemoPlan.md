
Demo Plan

1. Start demo on a demo repo with existing .task data
2. Then demo how to initialize on a new repository?


Procedure

#### 1. Open task app.
```
$ task
```

#### 2. Lists all tasks by due date in reverse chronological order (meaning the task that is due soonest is shown at the top)

```
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
```
#### 3. Create a new task

```
> new "Write headers for hash table" due="3 days"
```

#### 4. Show tasks by filter
```
> show --filter="Implement BST Node"

task a265bfa1c253019b96163a82a37c9d1c1332ac1a
Due: Mon Nov 24, 2016

	Implement BST Node

task 252bc06763afb3b6c2a0802f7346700ab55f46f5
Due: Mon Nov 26, 2016

	Implement BST Node
```
#### 5. Delete duplicate task
```
> delete 252b
Deleted task 252bc06763afb3b6c2a0802f7346700ab55f46f5
```
#### 6. Show command history
```
> history
delete 252bc06 "Implement BST Node"
update a265bfa status: backlog -> in-progress
create a265bfa "Implement BST Node"
```
#### 7. Undo delete
```
> undo
Undo delete of 252bc06763afb3b6c2a0802f7346700ab55f46f5
```

#### 8. Save to file
```
> quit
$ task
> show 252b
task 252bc06763afb3b6c2a0802f7346700ab55f46f5
Due: Mon Nov 26, 2016

  Implement BST Node

```

#### 9. Run Diagnostic
```
> test
Staring test execution, please wait...
Testing Dictionary... Passed
Testing Binary Search Tree... Passed

Results:
Total Entries: 46
Total Runs: 1000
Load Factor: 7
Maximum accesses: 9
Minimum accesses: 1
Average Efficiency: 3
Maximum time: 546 ms.
Minimum time: <1 ms.
Average time: 2 ms.
```
