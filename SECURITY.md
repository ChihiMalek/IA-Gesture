# Security Policy

## Supported Versions

| Version | Supported |
|---|---|
| 1.0.x | ✅ |
| < 1.0 (pre-release / development snapshots) | ❌ |

## Scope

This project combines a Python computer-vision/ML application, an
Arduino/ESP32/ESP8266 firmware, and an MQTT-based communication layer using
a **public, unauthenticated broker (`broker.emqx.io`)** by default. Please
keep the following in mind when evaluating security-relevant reports:

- The default MQTT broker and topics (`assist/gesture`, `assist/object`) are
  **public and unauthenticated** — this is appropriate for a prototype/
  academic demo, but **anyone can publish/subscribe to these topics**. Do
  not rely on this configuration for production, safety-critical, or
  privacy-sensitive deployments without adding broker authentication,
  TLS, and access control.
- Wi-Fi credentials in `firmware/gesture_assistant/gesture_assistant.ino`
  are placeholders meant to be edited locally before flashing — never
  commit real credentials to a public fork/branch.
- This project does not process or store personally identifiable
  information beyond local webcam frames used transiently for gesture
  inference (frames are not persisted by default).

## Reporting a Vulnerability

If you discover a security vulnerability (e.g. a way to compromise the
embedded firmware, abuse the MQTT communication, or an unsafe dependency),
please **do not open a public issue**. Instead:

1. Report it privately via GitHub's **[Security Advisories](../../security/advisories/new)** feature (preferred), or
2. Contact a maintainer directly through the GitHub profile linked on their [commits](../../commits/main) or the [Authors section of the README](README.md#-authors).

Please include:

- A clear description of the vulnerability and its potential impact
- Steps to reproduce (proof of concept if possible)
- Affected file(s)/component(s) (Python script, firmware, MQTT config, etc.)
- Your suggested remediation, if you have one

## Response Process

- We aim to acknowledge reports within **7 days**.
- We will investigate, confirm, and work on a fix or documented mitigation.
- Once resolved, a fix will be released and credited to the reporter
  (unless anonymity is requested), and details will be published via a
  GitHub Security Advisory.

## Recommended Hardening for Production Use

If you intend to move beyond the academic/demo scope of this project,
consider:

- Switching to a private MQTT broker with TLS and username/password or
  certificate-based authentication.
- Storing Wi-Fi/MQTT credentials outside of source control (e.g.
  `secrets.h` excluded via `.gitignore`, or environment variables for the
  Python side).
- Validating/sanitizing all incoming MQTT payloads on the firmware side.
- Reviewing third-party Python dependencies (`requirements.txt`) regularly
  for known CVEs (e.g. via `pip-audit` or GitHub Dependabot alerts).

Thank you for helping keep this project and its users safe.
