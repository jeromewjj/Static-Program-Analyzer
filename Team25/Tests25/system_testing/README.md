# System Testing

### _Folder Layout_

Each folder contains the following files:

- `run.sh`: to run the system tests
- `xxx_source.txt`: The source program to be tested
- `xxx_query.txt`: The query to be tested against `xxx_source.txt`


### _Running a system test_

E.g: To run system test in `milestone_1/valid` folder,

1.  Open a terminal in the `milestone_1/valid` folder or `cd` into it.
2.  Run:
    
    ```bash
    chmod u+x run.sh
    ./run.sh
    ```


3. To view the results of the test, run the following command in the same folder:

    `python -m http.server 8000`

