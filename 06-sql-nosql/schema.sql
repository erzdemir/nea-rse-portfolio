-- Illustrative catalogue schema. Interview artefact only.

CREATE TABLE library (
    library_id      SERIAL PRIMARY KEY,
    name            TEXT NOT NULL UNIQUE,      -- e.g. JEFF-4.0
    kind            TEXT NOT NULL,             -- evaluated | processed | experimental
    released_on     DATE,
    doi             TEXT
);

CREATE TABLE nuclide (
    nuclide_id      SERIAL PRIMARY KEY,
    symbol          TEXT NOT NULL UNIQUE,      -- U235
    z               INTEGER NOT NULL,
    a               INTEGER NOT NULL
);

CREATE TABLE evaluation_file (
    file_id         SERIAL PRIMARY KEY,
    library_id      INTEGER NOT NULL REFERENCES library(library_id),
    nuclide_id      INTEGER NOT NULL REFERENCES nuclide(nuclide_id),
    mf              INTEGER NOT NULL,
    mt              INTEGER NOT NULL,
    temperature_k   NUMERIC(8,2),
    format          TEXT NOT NULL,             -- ENDF6 | ACE | PENDF
    sha256          CHAR(64) NOT NULL,
    processor       TEXT,                      -- NJOY-xxx / FRENDY-xxx
    object_uri      TEXT NOT NULL,
    UNIQUE (library_id, nuclide_id, mf, mt, temperature_k, format)
);

CREATE TABLE ingest_audit (
    audit_id        BIGSERIAL PRIMARY KEY,
    file_id         INTEGER REFERENCES evaluation_file(file_id),
    ingested_at     TIMESTAMPTZ NOT NULL DEFAULT now(),
    image_digest    TEXT,
    status          TEXT NOT NULL,
    message         TEXT
);

CREATE INDEX evaluation_file_lookup
    ON evaluation_file (nuclide_id, mf, mt);
