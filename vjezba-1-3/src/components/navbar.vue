<template>
  <nav class="navbar sticky-top navbar-expand navbar-light navbar-general">
    <span class="navbar-logo"
      ><logo class="mr-3 mb-1" />PIIS 2020
      <span class="subtitle-text ml-2">Matija Novosel</span></span
    >
    <div class="collapse navbar-collapse">
      <ul class="navbar-nav mx-auto">
        <li class="nav-item mr-3">
          <span
            @click="redirect({ name: 'vjezba-1-sat' })"
            class="badge badge-pill pill shadow"
            :class="{ 'active-route': route.name == 'vjezba-1-sat' }"
            >Vježba 1 - Sat</span
          >
        </li>
        <li class="nav-item mr-3">
          <span
            @click="redirect({ name: 'vjezba-1-dizalo' })"
            class="badge badge-pill pill shadow"
            :class="{ 'active-route': route.name == 'vjezba-1-dizalo' }"
            >Vježba 1 - Dizalo</span
          >
        </li>
        <li class="nav-item">
          <span
            @click="redirect({ name: 'vjezba-3' })"
            class="badge badge-pill pill shadow"
            :class="{ 'active-route': route.name == 'vjezba-3' }"
            >Vježba 3</span
          >
        </li>
      </ul>
    </div>
  </nav>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useRouter, useRoute } from "vue-router";
import logo from "@/components/logo.vue";

interface Route {
  name: string;
}

export default defineComponent({
  name: "navbar",
  components: {
    logo
  },
  setup() {
    const router = useRouter();
    const route = useRoute();

    function redirect(route: Route) {
      router.push({ name: route.name });
    }

    return {
      redirect,
      route
    };
  }
});
</script>

<style scoped>
.navbar-general {
  border-bottom: 1px solid var(--border-color-dark);
  height: var(--navbar-height);
  max-height: var(--navbar-height);
  box-shadow: 0px 3px 9px #888888;
  background-color: white;
}
.navbar-logo {
  position: absolute;
  left: 35px;
  top: 20px;
  font-size: 20px;
  color: #273849;
  font-family: "Dosis", "Source Sans Pro", "Helvetica Neue", Arial, sans-serif;
  font-weight: 500;
}
.subtitle-text {
  color: grey;
  font-size: 12px;
}
.pill {
  font-size: 12px;
  cursor: pointer;
  padding: 6px 12px;
  background-color: #273849;
  color: white;
}
.pill:hover {
  background-color: grey;
}
.active-route {
  background-color: var(--vue-logo-green);
}
</style>
