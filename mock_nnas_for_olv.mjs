// @ts-check
import express from 'express';

/** Parse CLI args like --key=value into an object. */
const args = Object.fromEntries(
  process.argv.slice(2).map((arg) => {
    const [key, value = ''] = arg.replace(/^--/, '').split('=');
    return [key, value];
  })
);

const config = {
  port: Number(args.port) || 3000,
  serviceToken: args.service_token || 'SERVICE_TOKEN',
  portalHost: args.portal_host || '0.0.0.0',
  apiHost: args.api_host || '0.0.0.0',
  n3dsHost: args.n3ds_host || '0.0.0.0',
};

const app = express();

app.post('/v1/api/oauth20/access_token/generate', (_req, res) => {
  res.type('xml').send(
    `<?xml version='1.0'?><OAuth20><access_token><token>a</token><refresh_token>a</refresh_token><expires_in>3600</expires_in></access_token></OAuth20>`
  );
});

app.get('/v1/api/provider/service_token/@me', (_req, res) => {
  res.type('xml').send(
    `<?xml version='1.0'?><service_token><token>${config.serviceToken}</token></service_token>`
  );
});

app.get('/v1/endpoint', (_req, res) => {
  res.type('xml').send(
    `<?xml version='1.0'?><result><has_error>0</has_error><version>1</version><endpoint><host>${config.apiHost}</host><api_host>${config.apiHost}</api_host><portal_host>${config.portalHost}</portal_host><n3ds_host>${config.n3dsHost}</n3ds_host></endpoint></result>`
  );
});

app.listen(config.port, () =>
  console.log(`Mock NNAS server listening on ${config.port}.
Change port: --port=42069
ServiceToken: --service_token="token"
Wii U host: --portal_host=localhost:3000`)
);
