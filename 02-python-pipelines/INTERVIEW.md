# How to present Project 2 (about 90 seconds)

Vacancy: integrated pipelines; frameworks for nuclear physics data;
consistency of business logic and system behaviour.

Open pipeline/sample_tape.txt and say:
  These fields are the catalogue key: material, MF, MT, temperature.

Open endf_ingest.py and say:
  Missing identifiers fail closed. The output is an audit record a
  SQL table or Invenio record can store.

Then run the good tape and the bad tape.
  Good tape prints JSON and exits 0.
  Bad tape prints an error and exits 1.

Close with:
  At the Data Bank I would put this guard in front of NJOY or FRENDY
  so a pipeline cannot start on an incomplete JEFF file.
