import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";

import "bootstrap";
import "bootstrap/dist/css/bootstrap.min.css";
import "@/assets/css/site.css";

import GroupBox from "@/components/group-box.vue";

const app = createApp(App);

// Plugins
app.use(store);
app.use(router);

// Global components
app.component("group-box", GroupBox);

app.mount("#app");