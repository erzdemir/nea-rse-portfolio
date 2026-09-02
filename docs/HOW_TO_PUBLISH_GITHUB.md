# Publish this folder as a GitHub repository

```bash
cd nea-rse-portfolio
git init
git add .
git commit -m "Interview portfolio for OECD NEA Data Bank Research Software Engineer"
gh repo create nea-rse-portfolio --public --source=. --remote=origin --push
```

Suggested repository name: `nea-rse-portfolio` or `oecd-nea-databank-rse`.

Keep it public only because every file here is synthetic. Do not add real ENDF tapes, ACE libraries, or employer code later.

In the interview, send the URL with one sentence:

> This is a structured map of the vacancy tools to my nuclear-data work, plus small artefacts I can walk through. It is interview material, not a claim that every cloud component has been in production.
