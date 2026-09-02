-- Processed ACE products for U235 fission in a named library
SELECT l.name, n.symbol, f.mt, f.temperature_k, f.processor, f.sha256
FROM evaluation_file f
JOIN library l ON l.library_id = f.library_id
JOIN nuclide n ON n.nuclide_id = f.nuclide_id
WHERE n.symbol = 'U235'
  AND f.mt = 18
  AND f.format = 'ACE'
  AND l.name = 'JEFF-4.0';

-- Ingests that succeeded but have no checksum (data-quality alarm)
SELECT a.audit_id, a.ingested_at, a.image_digest
FROM ingest_audit a
JOIN evaluation_file f ON f.file_id = a.file_id
WHERE a.status = 'accepted'
  AND (f.sha256 IS NULL OR length(f.sha256) <> 64);
