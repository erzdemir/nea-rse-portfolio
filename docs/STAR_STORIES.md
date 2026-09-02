# STAR stories mapped to the vacancy

Keep each story under 90 seconds. End with the Data Bank implication.

## 1. Nuclear data processing (Research and Analysis)

**Situation.** Evaluated files (ENDF / JEFF) are not what transport codes consume. They must be processed to ACE / other application formats and then checked against experiment.

**Task.** Process library files with NJOY and FRENDY, generate MCNP ACE, benchmark against EXFOR, inspect with JANIS.

**Action.** Built repeatable Linux processing chains. Compared evaluations visually and numerically in JANIS. Isolated processor version, temperature and interpolation as first-class metadata rather than comments in a filename.

**Result.** Defensible processed products and a comparison trail a colleague can rerun.

**Implication.** This is the Data Bank’s core product line: acquire, develop, improve, validate, distribute.

## 2. Business-logic isolation in pipelines (exactly their wording)

**Situation.** Scientific scripts quietly mix “the answer” with auxiliary flags, paths and debug prints. That is how two machines produce two numbers.

**Task.** Ingest high-velocity data while enforcing syntax and separating performance metrics from auxiliary inputs.

**Action.** Wrote modular Python frameworks with explicit validation and audit records. Failed closed when identifiers were missing.

**Result.** Predictable system behaviour; easier hand-over.

**Implication.** Quote the vacancy back: “ensuring consistency of business logic and system behaviour.”

## 3. Legacy migration without changing the answer

**Situation.** Legacy engineering procedures and databases that still encode the real rules.

**Task.** Re-implement into modern, collaborative structures without drifting the logic.

**Action.** Inventoried behaviour first. Used the old system as an oracle. Moved function behind clearer interfaces rather than translating syntax blindly.

**Result.** Modern structure, same decisions.

**Implication.** Directly addresses “re-implementation of functionality from legacy Java codebases.” Anchor the story to JANIS as the Data Bank’s living Java estate.

## 4. Exploratory vs production code (C++ / Fortran / HPC)

**Situation.** A CFD / digital-twin idea that starts as a research kernel.

**Task.** Keep the physics usable beyond the original author.

**Action.** Developed C++ and Fortran frameworks on Linux HPC, versioned in Git, with a path from experiment to something another engineer can run.

**Result.** Research code that did not die in a personal directory.

**Implication.** The job text distinguishes exploratory research code from long-term production software. Show you already live in that split.

## 5. Cross-functional liaison and committees

**Situation.** Physicists state requirements in physics language; infrastructure is owned by informaticians.

**Task.** Be the scientific computing contact.

**Action.** Translated requirements into pipelines and repository practice. Presented at NURETH and specialists’ meetings. Completed the OECD NEA International School on Simulation of Nuclear Reactor Systems.

**Result.** Shared vocabulary, fewer “it works on my cluster” surprises.

**Implication.** The post reports to the Head of the Data Bank and to expert groups. Communication is not a soft extra; it is in the job description.

## 6. Frameworks for benchmarks and application data

**Situation.** Experimental benchmark and aerosol-deposition datasets that outlive a single paper.

**Task.** Collect, store, manage.

**Action.** Designed storage and tracking so the dataset remains findable and checkable.

**Result.** A framework rather than a folder of spreadsheets.

**Implication.** “Create new frameworks for the collection, storage and management of data for nuclear energy applications, including nuclear physics data, nuclear energy experimental benchmarks.”
